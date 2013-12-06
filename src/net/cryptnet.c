#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>
#include <string.h>

#include "packet.h"
#include "network.h"
#include "../crypto/aes.h"
#include "../crypto/elgamal.h"

#define ARG_VERBOSE (0x1<<3)


#define IF_VERBOSE if(arg_flags&ARG_VERBOSE)
#define NOT_DIVISIBLE_BY %

int arg_flags;

extern int aes_blocksize;

void cnet_close(void)
{
	aes_close();
	net_close();
}


static int exchange_elgamal(eg_pub_key_t *local_pubkey, eg_priv_key_t local_privkey, eg_pub_key_t *remote_pubkey, int bitlength)
{
	int i;
	net_packet_t pk;

	IF_VERBOSE printf("Generating ElGamal public-private key pair");
	eg_init_key(local_pubkey,local_privkey);
	eg_init_key(remote_pubkey,NULL);
	eg_gen_key(local_pubkey,local_privkey,bitlength);

	IF_VERBOSE gmp_printf("Your public key is:\np = %Zd\ng = %Zd\nb = %Zd\n",
		local_pubkey->p,local_pubkey->g,local_pubkey->beta);

	// Send the three bigints
	for (i = 0; i < (sizeof(eg_pub_key_t)/sizeof(mpz_t)); i++) {
		mpz_to_pk(&pk,((mpz_t*) local_pubkey)[i]) ;
		net_send(&pk);
	}
	IF_VERBOSE printf("Sent the public key!\n");

	// Receive the bigints
	for (i = 0; i < (sizeof(eg_pub_key_t)/sizeof(mpz_t)); i++) {
		net_recv(&pk);
		pk_to_mpz(((mpz_t*) remote_pubkey)[i],&pk);
	}
	IF_VERBOSE printf("Received friend's public key...\n");

	IF_VERBOSE gmp_printf("Friend's public key is:\np = %Zd\ng = %Zd\nb = %Zd\n",
		remote_pubkey->p,remote_pubkey->g,remote_pubkey->beta);

	return 0;
}

static int initialize_aes(eg_pub_key_t *local_pubkey, eg_priv_key_t local_privkey, eg_pub_key_t *rem_pubkey)
{
	int i;
	char local_aes[AES_KEY_SIZE];
	char remote_aes[AES_KEY_SIZE];
	char aes_key[AES_KEY_SIZE];

	mpz_t aes_loc_z,aes_rem_z;

	eg_message_t aes_keysend;

	net_packet_t pk;

	aes_random_key(local_aes);

	IF_VERBOSE printf("Sending Secret key...\n");

	mpz_init(aes_loc_z);
	mpz_init(aes_rem_z);

	mpz_import(aes_loc_z, 16, 1, 1, 0, 0, local_aes);

	eg_encrypt(*rem_pubkey,aes_loc_z,&aes_keysend);


	// Send the ElGamal-encrypted message with this client's AES key
	for (i = 0; i < (sizeof(eg_message_t)/sizeof(mpz_t)); i++) {
		mpz_to_pk(&pk,((mpz_t*) &aes_keysend)[i]) ;
		net_send(&pk);
	}

	// Wait for the friend's AES key
	for (i = 0; i < (sizeof(eg_message_t)/sizeof(mpz_t)); i++) {
		net_recv(&pk);
		pk_to_mpz(((mpz_t*) &aes_keysend)[i],&pk);
	}

	eg_decrypt(*local_pubkey, local_privkey, aes_keysend, aes_rem_z);
	mpz_export(remote_aes, NULL, 1, 1, 0, 0, aes_rem_z);


	// XOR the two AES keys, to generate the full AES key
	for (i = 0; i < AES_KEY_SIZE; i ++) {
		aes_key[i] = local_aes[i] ^ local_aes[i];
	}

	aes_init(aes_key,"AAAAAAAAAAAAAAAA");

	return 0;
}

int cnet_handshake(int inflags, int bitlength)
{
	arg_flags = inflags;
	eg_pub_key_t local_pubkey, remote_pubkey;
	eg_priv_key_t local_privkey;

	exchange_elgamal(&local_pubkey, local_privkey, &remote_pubkey, bitlength);

	initialize_aes(&local_pubkey, local_privkey, &remote_pubkey);

	IF_VERBOSE printf("Handshake Complete!\n");

	return 0;
}

int cnet_send(net_packet_t *pk)
{
	size_t pksize = pk->size;

	if (pk->size NOT_DIVISIBLE_BY aes_blocksize) {
		pk->size = ((pk->size / aes_blocksize) + 1) * aes_blocksize;
		memset(pk+pksize, 0, pk->size - pksize);
	}
	if (pk->size >= sizeof(pk->body)) return -7;

	aes_encrypt(pk->body,pk->size);

	return net_send(pk);
}

int cnet_recv(net_packet_t *pk)
{
	int ret;
	ret = net_recv(pk);

	if (ret < 0) return ret;

	aes_decrypt(pk->body,pk->size);

	return ret;
}

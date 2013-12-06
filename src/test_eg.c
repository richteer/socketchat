#include <stdio.h>
#include <gmp.h>

#include "crypto/elgamal.h"

int main(int argc, char **argv)
{
	eg_pub_key_t public_key;
	eg_priv_key_t private_key;

	eg_message_t message;

	eg_init_key(&public_key, private_key);

	fprintf(stderr, "Testing eg_gen_key\n");
	eg_gen_key(&public_key, private_key, 1024);
	gmp_fprintf(stderr,
		    "p: %Zd\ng: %Zd\nbeta: %Zd\nalpha: %Zd\n",
		    public_key.p, public_key.g, public_key.beta, private_key);
	fprintf(stderr, "Finished eg_gen_key\n");
	
	fprintf(stderr, "Testing eg_encrypt\n");
	mpz_t plain; mpz_init_set_ui(plain, 4);
	eg_encrypt( public_key, plain, &message );
	gmp_fprintf(stderr, "message: %Zd\nmask: %Zd\n", message.message, message.mask);
	mpz_clear(plain);
	fprintf(stderr, "Finished eg_encrypt\n");

	fprintf(stderr, "Testing eg_decrypt\n");
	mpz_init(plain);
	eg_decrypt(public_key, private_key, message, plain);
	gmp_fprintf(stderr, "plaintext: %Zd\n", plain);
	fprintf(stderr, "Finished eg_decrypt\n");

	return 0;
}

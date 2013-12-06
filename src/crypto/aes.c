#include <mcrypt.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "aes.h"

MCRYPT aes_td;
char aes_key[17] = {0};
char aes_iv[17] = {0};
int aes_blocksize = -1;


int aes_init(char* key, char* iv)
{
	strncpy(aes_key,key,16);
	strncpy(aes_iv,iv,16);
	aes_td = mcrypt_module_open("rijndael-128", NULL, "cbc", NULL);
	aes_blocksize = mcrypt_enc_get_block_size(aes_td);

	return  0;
}

void aes_close()
{
	mcrypt_module_close(aes_td);
}

int aes_encrypt(char* buffer, size_t bufsize)
{
	if (bufsize % aes_blocksize) return -1;

	mcrypt_generic_init(aes_td,aes_key,16,aes_iv);
	mcrypt_generic(aes_td,buffer,bufsize);
	mcrypt_generic_deinit(aes_td);

	return 0;
}

int aes_decrypt(char* buffer, size_t bufsize)
{
	if (bufsize % aes_blocksize) return -1;

	mcrypt_generic_init(aes_td,aes_key,16,aes_iv);
	mdecrypt_generic(aes_td,buffer,bufsize);
	mcrypt_generic_deinit(aes_td);

	return 0;
}

void aes_random_key(char* key)
{
	int i;
	int randomData = open("/dev/urandom", O_RDONLY);

	for (i = 0; i < (AES_KEY_SIZE/sizeof(unsigned)); i++) {
		read(randomData, ((unsigned*) key) + i,sizeof(unsigned));
	}

	close(randomData);
}


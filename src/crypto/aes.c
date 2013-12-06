#include <mcrypt.h>
#include <stdlib.h>
#include <string.h>
//#include <stdio.h>

#define BUF_SIZE 256

MCRYPT cr_td;
char cr_key[17] = {0};
char cr_iv[17] = {0};
int cr_blocksize = -1;


int cr_init(char* key, char* iv)
{
	strncpy(cr_key,key,16);
	strncpy(cr_iv,iv,16);
	cr_td = mcrypt_module_open("rijndael-128", NULL, "cbc", NULL);
	cr_blocksize = mcrypt_enc_get_block_size(cr_td);

	return  0;
}

void cr_close()
{
	mcrypt_module_close(cr_td);
}

int cr_encrypt(char* buffer, size_t bufsize)
{
	if (bufsize % cr_blocksize) return -1;

	mcrypt_generic_init(cr_td,cr_key,16,cr_iv);
	mcrypt_generic(cr_td,buffer,BUF_SIZE);
	mcrypt_generic_deinit(cr_td);

	return 0;
}

int cr_decrypt(char* buffer, size_t bufsize)
{
	if (bufsize % cr_blocksize) return -1;

	mcrypt_generic_init(cr_td,cr_key,16,cr_iv);
	mdecrypt_generic(cr_td,buffer,BUF_SIZE);
	mcrypt_generic_deinit(cr_td);

	return 0;
}


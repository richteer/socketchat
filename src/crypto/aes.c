#include <mcrypt.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define BUF_SIZE 256

MCRYPT cr_td;
char cr_key[17] = {0};
char cr_iv[17] = {0};

int cr_init(char* key)
{
	strncpy(cr_key,key,16);
	cr_td = mcrypt_module_open("rijndael-128", NULL, "cbc", NULL);
	mcrypt_generic_init(cr_td,cr_key,sizeof(cr_key),cr_iv);

	/* TODO: Fix this */
	return  (cr_td == MCRYPT_FAILED) ? -1 : 0;
}

int cr_close()
{
	mcrypt_generic_deinit(td);
	mcrypt_generic_close(td);
}

int cr_encrypt(char* buffer)
{
	mcrypt_generic(cr_td,buffer,BUF_SIZE);

	return 0;
}



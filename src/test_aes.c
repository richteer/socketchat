#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "crypto/aes.h"

int main()
{
	char string[256] = {0};
	strcpy(string,"test");

	cr_init("derpderpderpderp","AAAAAAAAAAAAAAAA");

	printf("Plaintext before: %s\n",string);

	cr_encrypt(string);	
	cr_decrypt(string);

	printf("Plaintext after : %s\n",string);


	//cr_close();

	return 0;
}
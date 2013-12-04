#include <stdio.h>
#include <stdlib.h>

#include <gmp.h>

#include "key.h"

void encrypt_char(mpz_t rop, int c, pubkey k);

int main(int argc, char **argv)
{
	if (argc < 3)
	{
		printf("Usage: %s inputfile outputfile [pubkeyfile]\n", argv[0]);
		exit(0);
	}

	char *ptxtfname = argv[1];
	char *ctxtfname = argv[2];
	char *pkeyfname;

	if (argc != 4)
	{
		pkeyfname = "id_rsa.pub";
	} else {
		pkeyfname = argv[3];
	}

	FILE *fptxt = fopen(ptxtfname, "r");
	FILE *fctxt = fopen(ctxtfname, "w");
	FILE *fpkey = fopen(pkeyfname, "r");

	pubkey pkey;
	mpz_init(pkey.n);
	mpz_init(pkey.e);
	
	gmp_fscanf(fpkey, "%Zd", &(pkey.n));
	gmp_fscanf(fpkey, "%Zd", &pkey.e);
	
	int c = getc(fptxt); 
	int count = 0;
	mpz_t next; mpz_init(next);
	while (c != EOF)
	{
		encrypt_char(next, c, pkey);
		gmp_fprintf(fctxt, "%Zd\n", next);
		c = getc(fptxt);
	}
}

void encrypt_char(mpz_t rop, int c, pubkey k)
{
	mpz_set_ui(rop, c);
	mpz_powm(rop, rop, k.e, k.n);
}

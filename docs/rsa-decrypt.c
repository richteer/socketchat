#include <stdio.h>
#include <stdlib.h>

#include <gmp.h>

#include "key.h"

void decrypt_char(mpz_t rop, int c, key k);

int main(int argc, char **argv)
{
	if (argc < 3)
	{
		printf("Usage: %s inputfile outputfile [privkeyfile]\n", argv[0]);
		exit(0);
	}

	char *ptxtfname = argv[2];
	char *ctxtfname = argv[1];
	char *pkeyfname;

	if (argc != 4)
	{
		pkeyfname = "id_rsa";
	} else {
		pkeyfname = argv[3];
	}

	FILE *fptxt = fopen(ptxtfname, "r");
	FILE *fctxt = fopen(ctxtfname, "w");
	FILE *fpkey = fopen(pkeyfname, "r");

	key pkey;
	mpz_init(pkey.p);
	mpz_init(pkey.q);
	mpz_init(pkey.n);
	mpz_init(pkey.phi);
	mpz_init(pkey.e);
	mpz_init(pkey.d);
	
	gmp_fscanf(fpkey, "%Zd", &pkey.p);
	gmp_fscanf(fpkey, "%Zd", &pkey.q);
	gmp_fscanf(fpkey, "%Zd", &pkey.n);
	gmp_fscanf(fpkey, "%Zd", &pkey.phi);
	gmp_fscanf(fpkey, "%Zd", &pkey.e);
	gmp_fscanf(fpkey, "%Zd", &pkey.d);
	
	int c = getc(fptxt); 
	int count = 0;
	mpz_t next; mpz_init(next);
	while (c != EOF)
	{
		decrypt_char(next, c, pkey);
		gmp_fprintf(fctxt, "%Zd\n", next);
		c = getc(fptxt);
	}
}

void decrypt_char(mpz_t rop, int c, key k)
{
	mpz_set_ui(rop, c);
	mpz_powm(rop, rop, k.d, k.n);
}

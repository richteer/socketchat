#ifndef _elgamal_h_
#define _elgamal_h_

typedef struct eg_pub_key_s
{
	mpz_t p;
	mpz_t n;
} eg_pub_key_t;

typedef mpz_t eg_priv_key_t;

#endif

#ifndef _elgamal_h_
#define _elgamal_h_

typedef struct eg_pub_key_s
{
	mpz_t p;	// k-bit safe prime
	mpz_t g;	// generator for p
	mpz_t beta;	// g^a, where a is the private exponent
} eg_pub_key_t;

typedef mpz_t eg_priv_key_t;

// To ignore an arg, pass NULL
void eg_init_key( eg_pub_key_t pub, eg_priv_key_t priv );

void eg_gen_key( eg_pub_key_t pub, eg_priv_key_t priv, int bitlength );
void eg_encrypt( eg_pub_key_t pub, char *ptext, char *ctext );
void eg_decrypt( eg_pub_key_t pub, eg_priv_key_t priv, char *ctext, char *ptext );

#endif

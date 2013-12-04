/*************************************************************************
 * Implementation of ElGamal in c
 * written by millere and richteer
 * 
 * Note - don't use this for anything whrer security matters.
 *        We haven't confirmed that this code does what it
 *        says it does.
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

#include "number.h"
#include "elgamal.h"

void eg_init_key( eg_pub_key_t pub, eg_priv_key_t priv )
{
	mpz_init(pub.p);
	mpz_init(pub.g);
	mpz_init(pub.beta);

	if (NULL != (void *) priv) {
		mpz_init(priv);
	}
}

void eg_gen_key( eg_pub_key_t pub, eg_priv_key_t priv, int bitlength )
{
	mpz_t q; mpz_init(q);
	gmp_randstate_t r_state;
	get_rand_seed(r_state);

}

void eg_encrypt( eg_pub_key_t pub, char *ptext, char *ctext )
{
	// TODO
}

void eg_decrypt( eg_pub_key_t pub, eg_priv_key_t priv, char *ctext, char *ptext )
{
	// TODO
}

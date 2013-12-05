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

void eg_init_key( eg_pub_key_t *pub, eg_priv_key_t priv )
{
	mpz_init(pub->p);
	mpz_init(pub->g);
	mpz_init(pub->beta);

	if (NULL != (void *) priv) {
		mpz_init(priv);
	}
}

void eg_gen_key( eg_pub_key_t *pub, eg_priv_key_t priv, int bitlength )
{
	gmp_randstate_t r_state;
	get_rand_seed(r_state);

	gen_safe_prime(pub->p, bitlength, r_state);
	gen_generator(pub->g, pub->p, r_state);

	mpz_t temp; mpz_init_set(temp, pub->p);
	mpz_sub_ui(temp, temp, 2);
	mpz_urandomm(priv, r_state, temp);
	mpz_add_ui(priv, priv, 1);
	mpz_clear(temp);

	mpz_powm(pub->beta, pub->g, priv, pub->p);

	gmp_randclear(r_state);

}

void eg_encrypt( eg_pub_key_t pub, mpz_t plain, eg_message_t *cipher )
{
	gmp_randstate_t r_state;
	get_rand_seed(r_state);
	
	mpz_t y; mpz_init(y);
	mpz_t c1; mpz_init(c1);
	mpz_t c2; mpz_init(c2);
	mpz_t s; mpz_init(s);
	
	mpz_inits(cipher->mask, cipher->message, NULL);
	gen_range_ui(y, 1, pub.p, r_state);
	mpz_powm(c1, pub.g, y, pub.p);
	mpz_powm(s, pub.beta, y, pub.p);
	mpz_mul(c2, plain, s);
	mpz_mod(c2, c2, pub.p);

	mpz_inits(cipher->mask, cipher->message, NULL);
	mpz_set(cipher->mask, c1);
	mpz_set(cipher->message, c2);

	mpz_clears(y, c1, c2, s, NULL);
}

void eg_decrypt( eg_pub_key_t pub, eg_priv_key_t priv, eg_message_t cipher, mpz_t plain )
{
	mpz_t temp; mpz_init(temp);

	mpz_powm( temp, cipher.mask, priv, pub.p );
	mpz_invert( temp, temp, pub.p );
	mpz_mul( plain, cipher.message, temp );
	mpz_mod( plain, plain, pub.p );

	mpz_clear(temp);
}

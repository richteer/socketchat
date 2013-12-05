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

	mpz_inits(cipher->mask, cipher->message, NULL);
	gen_range_ui( cipher->mask, 2, pub.p, r_state );

	// message = beta^mask * plain (mod p)
	mpz_powm( cipher->message, pub.beta, cipher->mask, pub.p );
	mpz_mul( cipher->message, cipher->message, plain);
	mpz_mod( cipher->message, cipher->message, pub.p );
}

void eg_decrypt( eg_pub_key_t pub, eg_priv_key_t priv, eg_message_t *cipher, mpz_t plain )
{
	// TODO
}

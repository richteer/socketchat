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


#include "elgamal.h"

void eg_gen_key( eg_pub_key_t pub, eg_priv_key_t priv, int bitlength )
{
	// TODO
}

void eg_encrypt( eg_pub_key_t pub, char *ptext, char *ctext )
{
	// TODO
}

void eg_decrypt( eg_pub_key_t pub, eg_priv_key_t priv, char *ctext, char *ptext )
{
	// TODO
}

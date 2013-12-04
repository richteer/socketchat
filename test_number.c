#include <stdio.h>
#include <gmp.h>

#include "number.h"

int main()
{
	mpz_t a;
	mpz_init(a);
	gmp_randstate_t r_state;
	get_rand_seed(r_state);
	gen_number(10, a, r_state);
	gmp_fprintf(stderr,"Random number: %Zd\n", a);
	gen_prime(10, a, r_state);
	gmp_fprintf(stderr,"Random prime: %Zd\n", a);
	
	return 0;
}

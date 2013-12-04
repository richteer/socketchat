#include <stdio.h>
#include <gmp.h>

#include "number.h"

int main()
{
	mpz_t a;
	mpz_init(a);
	gmp_randstate_t r_state;
	get_rand_seed(r_state);
	gen_number(a, 10, r_state);
	gmp_fprintf(stderr,"Random number: %Zd\n", a);
	gen_prime(a, 10, r_state);
	gmp_fprintf(stderr,"Random prime: %Zd\n", a);
	gen_safe_prime(a, 5, r_state);
	gmp_fprintf(stderr, "Random safe prime: %Zd\n", a);

	mpz_clear(a);
	gmp_randclear(r_state);
	return 0;
}

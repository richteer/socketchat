#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <gmp.h>

#include "number.h"


void gen_prime(mpz_t p, int bitlength, gmp_randstate_t r_state)
{
        gen_number(p, bitlength, r_state);

        while (mpz_probab_prime_p(p, 25) < 1)
        {
                gen_number(p, bitlength, r_state);
        }
    
}

void gen_safe_prime(mpz_t p, int bitlength, gmp_randstate_t r_state)
{
	mpz_t q; mpz_init(q);
	mpz_set_ui(p, 1);

	while ( ! mpz_probab_prime_p(q, 25) )
	{
		gen_prime(q, bitlength - 1, r_state);
		mpz_mul_ui(p, q, 2);
		mpz_add_ui(p, p, 1);
	}
	mpz_clear(q);
}

void gen_number(mpz_t p, int bitlength, gmp_randstate_t r_state)
{
        mpz_t min_value, max_value, two;
        mpz_init(min_value);
        mpz_init(max_value);
        mpz_init(two);
        
        mpz_set_ui(two, 2);
        
        mpz_pow_ui(min_value, two, bitlength - 1);
        mpz_pow_ui(max_value, two, bitlength);
        
        mpz_sub(max_value, max_value, min_value);
	mpz_urandomm(p, r_state, max_value);
        mpz_add(p, p, min_value);
	
	mpz_clear(min_value);
	mpz_clear(max_value);
	mpz_clear(two);
}

void get_rand_seed(gmp_randstate_t r_state)
{
	int randomData = open("/dev/urandom", O_RDONLY);
	unsigned long int seed;
	read(randomData, &seed, sizeof(seed));
	gmp_randinit_default(r_state);
	gmp_randseed_ui(r_state, seed);
}	

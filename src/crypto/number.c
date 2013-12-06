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
	mpz_set_ui(p, 4);

	while ( mpz_probab_prime_p(p, 25) == 0)
	{
		gen_prime(q, bitlength - 1, r_state);
		mpz_mul_ui(p, q, 2);
		mpz_add_ui(p, p, 1);
	}
	mpz_clear(q);
}

void gen_generator(mpz_t g, mpz_t p, gmp_randstate_t r_state)
{
	int done = 0;
	mpz_t temp; mpz_init(temp);
	mpz_t q; mpz_init_set(q, p);
	mpz_t max; mpz_init(max);
	mpz_sub_ui(max, p, 2);
	mpz_sub_ui(q, q, 1);
	mpz_cdiv_q_ui(q, q, 2);

	while (!done)
	{
		mpz_urandomm(g, r_state, max);
		mpz_add_ui(g, g, 2);

		mpz_powm_ui(temp, g, 1, p);
		if (mpz_cmp_ui(temp, 1) == 0) { // g^1 == 1 (mod p)
			done = 0;
			continue;
		} else {
			done = 1;
		}

		mpz_powm_ui(temp, g, 2, p);
		if (mpz_cmp_ui(temp, 1) == 0) {
			done = 0;
			continue;
		} else {
			done = 1;
		}

		mpz_powm(temp, g, q, p);
		if (mpz_cmp_ui(temp, 1) == 0 ) {
			done = 0;
			continue;
		} else {
			done = 1;
		}
			
	}

	mpz_clears(temp, q, NULL);
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
	close(randomData);
}

void gen_range( mpz_t rop, mpz_t min, mpz_t max, gmp_randstate_t r_state )
{
	mpz_t tmax;
	mpz_init(tmax);

	mpz_sub(tmax, max, min);
	mpz_urandomm(rop, r_state, tmax);
	mpz_add(rop, rop, min);

	mpz_clear(tmax);
}

void gen_range_ui( mpz_t rop, unsigned long int min, mpz_t max, gmp_randstate_t r_state)
{
	mpz_t tmin; mpz_init_set_ui(tmin, min);
	gen_range(rop, tmin, max, r_state);
	mpz_clear(tmin);
}

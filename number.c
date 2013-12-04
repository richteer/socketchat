#include <stdio.h>
#include <fcntl.h>
#include <gmp.h>

#include "number.h"


void gen_prime(int bitlength, mpz_t p, gmp_randstate_t r_state)
{
        gen_number(bitlength, p, r_state);
	fprintf(stderr, "in gen_prime\n");

        while (mpz_probab_prime_p(p, 25) < 1)
        {
                gen_number(bitlength, p, r_state);
        }
    
}

void gen_number(int bitlength, mpz_t p, gmp_randstate_t r_state)
{
        mpz_t min_value, max_value, two;
        mpz_init(min_value);
        mpz_init(max_value);
        mpz_init(two);
        
        mpz_set_ui(two, 2);
        
        mpz_pow_ui(min_value, two, bitlength - 1);
        mpz_pow_ui(max_value, two, bitlength);
        
        mpz_sub(max_value, max_value, min_value);
        gmp_fprintf(stderr, "r_state: %X\n", *r_state);
	mpz_urandomm(p, r_state, max_value);
        mpz_add(p, p, min_value);
}

void get_rand_seed(gmp_randstate_t r_state)
{
	int randomData = open("/dev/urandom", O_RDONLY);
	unsigned long int seed;
	read(randomData, &seed, sizeof(seed));
	fprintf(stderr, "seed from /dev/random: %d\n", seed);
	gmp_randinit_default(r_state);
	gmp_randseed_ui(r_state, 3);

	//mpz_t test, max;
	//mpz_init(test); mpz_init(max);
	//mpz_set_ui(max, 50);
	//fprintf(stderr, "Before\n");
	//mpz_urandomm(test, r_state, max);
	//fprintf(stderr, "After\n");
}

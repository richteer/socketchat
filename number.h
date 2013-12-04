#ifndef _number_h_
#define _number_h_

void gen_number( int bitlength, mpz_t p, gmp_randstate_t r_state);
void gen_prime( int bitlength, mpz_t p, gmp_randstate_t r_state);
void get_rand_seed( gmp_randstate_t r_state);

#endif

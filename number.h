#ifndef _number_h_
#define _number_h_

void gen_number( mpz_t p, int bitlength, gmp_randstate_t r_state );
void gen_prime( mpz_t p, int bitlength, gmp_randstate_t r_state );
void gen_safe_prime( mpz_t p, int bitlength, gmp_randstate_t r_state );
void gen_generator( mpz_t g, mpz_t p, gmp_randstate_t r_state );
void get_rand_seed( gmp_randstate_t r_state );

#endif

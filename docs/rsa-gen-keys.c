#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <gmp.h>

#include "key.h"

void gen_primes(int bitlength, mpz_t *p, mpz_t *q);
void gen_phi(mpz_t *phi, mpz_t *p, mpz_t *q);
void gen_e(mpz_t *e, mpz_t *phi);
int get_rand_seed();
void create_files(FILE *prvkey, FILE *pubkey, key k);

int main(int argc, char **argv)
{
	if (argc <  2) {
		printf("Usage: %s bitlength [pubkeyfilename prvkeyfilename]\n", argv[0]);
		exit(-1);
	}

	char *pubkeyfilename;
	char *prvkeyfilename;

	if (argc == 4) {
		prvkeyfilename = argv[2];
		pubkeyfilename = argv[3];
	} else {
		prvkeyfilename = "id_rsa";
		pubkeyfilename = "id_rsa.pub";
	}

	FILE *prvkey = fopen(prvkeyfilename, "w");
	FILE *pubkey = fopen(pubkeyfilename, "w");

	int primebitlength = atoi(argv[1]);

	key k;
	mpz_init(k.p);
	mpz_init(k.q);
	mpz_init(k.n);
	mpz_init(k.phi);
	mpz_init(k.e);
	mpz_init(k.d);

	gen_primes(primebitlength, &k.p, &k.q);
	gen_phi(&k.phi, &k.p, &k.q);
	gen_e(&k.e, &k.phi);
	mpz_invert(k.d, k.e, k.phi);
	mpz_mul(k.n, k.p, k.q);

	create_files(prvkey, pubkey, k);
	fclose(prvkey);
	fclose(pubkey);
	return 0;
}

void gen_number(int bitlength, mpz_t *p, gmp_randstate_t r_state)
{
	mpz_t min_value, max_value, two;
	mpz_init(min_value);
	mpz_init(max_value);
	mpz_init(two);

	mpz_set_ui(two, 2);
	
	mpz_pow_ui(min_value, two, bitlength - 1);
	mpz_pow_ui(max_value, two, bitlength);
	
	mpz_sub(max_value, max_value, min_value);
	mpz_urandomm(*p, r_state, max_value);
	mpz_add(*p, *p, min_value);
}

void gen_prime(int bitlength, mpz_t *p, gmp_randstate_t r_state)
{
	gen_number(bitlength, p, r_state);
	
	while (mpz_probab_prime_p(*p, 25) < 1)
	{
		gen_number(bitlength, p, r_state);
	}
	
}

void gen_primes(int bitlength, mpz_t *p, mpz_t *q)
{
	gmp_randstate_t r_state;
	gmp_randinit_default(r_state);

	gmp_randseed_ui(r_state, get_rand_seed()); 
	
	gen_prime(bitlength, p, r_state);
	do
	{
		gen_prime(bitlength, q, r_state);
	} while (!mpz_cmp(*p, *q)); // while p and q are equal
}

void gen_phi(mpz_t *phi, mpz_t *p, mpz_t *q)
{
	mpz_sub_ui(*p, *p, 1);
	mpz_sub_ui(*q, *q, 1);
	mpz_mul(*phi, *p, *q); // phi = (p-1)(q-1)
	mpz_add_ui(*p, *p, 1);
	mpz_add_ui(*q, *q, 1);
}

void gen_e(mpz_t *e, mpz_t *phi)
{
	gmp_randstate_t r_state;
	gmp_randinit_default(r_state);
	gmp_randseed_ui(r_state, get_rand_seed());
	
	mpz_t gcd; mpz_init(gcd);

	do
	{
		mpz_urandomm(*e, r_state, *phi);
		mpz_gcd(gcd, *e, *phi);
	} while (mpz_cmp_ui(gcd, 1) != 0);
}

int get_rand_seed()
{
	int randomData = open("/dev/random", O_RDONLY);
	int seed;
	int ret = read(randomData, &seed, sizeof(seed));
	return seed;
}


void create_files(FILE *prvkey, FILE *pubkey, key k)
{
	gmp_fprintf(prvkey, "%Zd\n", k.p);
	gmp_fprintf(prvkey, "%Zd\n", k.q);
	gmp_fprintf(prvkey, "%Zd\n", k.n);
	gmp_fprintf(prvkey, "%Zd\n", k.phi);
	gmp_fprintf(prvkey, "%Zd\n", k.e);
	gmp_fprintf(prvkey, "%Zd\n", k.d);

	gmp_fprintf(pubkey, "%Zd\n", k.n);
	gmp_fprintf(pubkey, "%Zd\n", k.e);
}

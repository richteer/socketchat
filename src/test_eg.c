#include <stdio.h>
#include <gmp.h>

#include "crypto/elgamal.h"

int main()
{
	eg_pub_key_t public_key;
	eg_priv_key_t private_key;

	eg_init_key(&public_key, private_key);

	fprintf(stderr, "Testing eg_gen_key\n");
	eg_gen_key(&public_key, private_key, 10);
	gmp_fprintf(stderr,
		    "p: %Zd\ng: %Zd\nbeta: %Zd\nalpha: %Zd\n",
		    public_key.p, public_key.g, public_key.beta, private_key);
	fprintf(stderr, "Finished eg_gen_key\n");

	return 0;
}

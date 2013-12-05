#include <stdio.h>
#include <gmp.h>

#include "crypto/elgamal.h"

int main()
{
	eg_pub_key_t public_key;
	eg_priv_key_t private_key;

	eg_message_t message;

	eg_init_key(&public_key, private_key);

	fprintf(stderr, "Testing eg_gen_key\n");
	eg_gen_key(&public_key, private_key, 10);
	gmp_fprintf(stderr,
		    "p: %Zd\ng: %Zd\nbeta: %Zd\nalpha: %Zd\n",
		    public_key.p, public_key.g, public_key.beta, private_key);
	fprintf(stderr, "Finished eg_gen_key\n");
	
	fprintf(stderr, "Testing eg_encrypt\n");
	mpz_t plain; mpz_init_set_ui(plain, 4);
	eg_encrypt( public_key, plain, &message );
	gmp_fprintf(stderr, "message: %Zd\nmask: %Zd\n", message.message, message.mask);
	fprintf(stderr, "Finished eg_encrypt\n");

	return 0;
}

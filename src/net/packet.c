#include <stdlib.h>
#include <string.h>

#include "packet.h"

void mpz_to_pk(net_packet_t *pk, mpz_t num)
{
	if (NULL == pk);

	mpz_export(pk->body, 
		       &(pk->size), 1, 1, 
		       0,0, 
		       num);

	printf("MPZ to PK size report: %d\n",pk->size);

}

void pk_to_mpz(mpz_t num, net_packet_t *pk)
{
	if (NULL == pk) return;

	mpz_import (num, 
		        pk->size, 1, 1, 
		        0, 0, 
		        pk->body);
}

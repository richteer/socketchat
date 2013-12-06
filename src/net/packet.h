#ifndef _packet_h_
#define _packet_h_
#include <gmp.h>

typedef struct {
	size_t size;
	char body[1024];
} net_packet_t;

void mpz_to_pk(net_packet_t *pk, mpz_t num);
void pk_to_mpz(mpz_t num, net_packet_t *pk);


#endif
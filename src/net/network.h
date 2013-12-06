#ifndef _network_h_
#define _network_h_

#include "packet.h"

#define DEBUG 1

int net_connect(char* ip,char* port);
int net_listen(char* port);
void net_close();

int net_send(net_packet_t* pk);
int net_recv(net_packet_t* pk);

#endif
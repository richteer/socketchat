#ifndef _cryptnet_h_
#define _cryptnet_h_

int cnet_handshake(int);
void cnet_close(void);
int cnet_send(net_packet_t *pk);
int cnet_recv(net_packet_t *pk);


#endif
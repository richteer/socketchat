
#define DEBUG 1

typedef struct {
	int next;
	char body[256]
} net_packet_t;


int net_init(char* ip,char* port);
int net_close();

int net_send(net_packet_t* pk);
int net_recv(net_packet_t* pk);
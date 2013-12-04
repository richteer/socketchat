#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <netdb.h>

#include "network.h"

int sfd = -1;
struct sockaddr serv_addr;
socklen_t serv_socksize;

int net_init(char* ip, char* port)
{
	struct addrinfo hints, *servinfo, *p;
	int rv;
	int retval;

	memset(&hints,0,sizeof(hints));
	
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;

	if ((NULL == ip) || (NULL == port)) {
		fprintf(stderr,"Invalid server or port!\n");
		return -1;
	}

	if ((rv = getaddrinfo(ip,port,&hints,&servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return -2;
	}

	for (p = servinfo; p != NULL; p = p->ai_next) {
		if (-1 != (sfd = socket(p->ai_family, p->ai_family, p->ai_protocol)))
			break;
	}

	if (NULL == p) {
		fprintf(stderr, "Could not create a socket!\n");
		retval = -3;
		goto cleanup;
	}

	if (0 != bind(sfd, p->ai_addr, p->ai_addrlen)) {
		#if DEBUG
			perror("bind error");
		#endif

		retval = -4;
		close(sfd);
		sfd = -1;
		goto cleanup;
	}

	memcpy(&serv_addr,p->ai_addr,p->ai_addrlen);
	serv_socksize = p->ai_addrlen;

cleanup:
	freeaddrinfo(servinfo);

	return retval;
}

void net_close()
{
	close(sfd);
}

int net_send(net_packet_t* pk)
{
	int ret;
	if (NULL == pk) return -2;

	if (-1 == (ret = sendto(sfd,pk,sizeof(net_packet_t),0,&serv_addr,serv_socksize)))
		perror("send failed");
	return ret;
}

int net_recv(net_packet_t* pk)
{
	int ret;
	struct sockaddr sa;
	socklen_t sl;

	if (NULL == pk) return -2;

	if (-1 == (ret = recvfrom(sfd,pk,sizeof(net_packet_t),0,&sa,&sl)))
		perror("recvfrom failed");

	return ret;
}
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

#include "network.h"

#define ARG_VERBOSE (0x1 << 1)

unsigned arg_flags = 0;
char* serverip;
char* serverport;


int handle_args(int,char**);
void show_help(void);

void handle_sigint(int x) { net_close(); exit(0); }

int main(int argc, char **argv)
{
	if ((argc < 3) && handle_args(argc,argv)) {
		fprintf("Error parsing arguments\n");
		exit(1);
	}
	
	printf("Client started, hit ^C to exit\n");
	if (0 != net_init(NULL,"12345")) {
		fprintf("Could not initialize the network!\n");
		exit(2);
	}
	signal(SIGINT,handle_sigint);

	/* DO SERVER-LIKE STUFF HERE */

	return 0;
}

int handle_args(int argc, char** argv) 
{
	int i, ret = 0;
	for (i = 1; i < argc -2; i++) {asdjkalsdjkhashkjdakjlhsdkjh
		switch(argv[i][1]) {
			case 'v': arg_flags |= ARG_VERBOSE; break;
			case 'h': show_help(); exit(2); 	break;
			default: ret = -1;
		}
	}

	serverip = argv[i++]; 
	serverport = argv[i]; 

	return ret;
}

void show_help()
{
	fprintf(stderr,"Not implemented yet!\n");
	return;
}
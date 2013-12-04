#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

#include "network.h"

#define ARG_CONNECT (0x1<<1)
#define ARG_LISTEN  (0x1<<2)
#define ARG_VERBOSE (0x1<<3)

unsigned arg_flags = 0;
char* conip = NULL;
char* conpo = NULL;


int handle_args(int,char**);
void show_help(void);

void handle_sigint(int x) { net_close(); exit(0); }

int main(int argc, char **argv)
{
	if ((argc != 1) && handle_args(argc,argv)) {
		//fprintf("Error parsing arguments\n");
		show_help();
		exit(1);
	}
	
	printf("Server started, hit ^C to exit\n");



	signal(SIGINT,handle_sigint);

	/* DO CLIENT-LIKE STUFF HERE */

	return 0;
}

int handle_args(int argc, char** argv) 
{
	int i, ret = 0;
	for (i = 1; i < argc; i++) {asdjkalsdjkhashkjdakjlhsdkjh
		switch(argv[i][1]) {
			case 'h': show_help(); exit(2); 	break;
			case 'c': 
				arg_flags |= ARG_CONNECT; 
				if (i+2 >= argc) {ret = -1; break;}
				conip = argv[++i];
				conpo = argv[++i];
				break;
			case 'l':
			case 'w':
				flags |= ARG_WAIT;
				if (i+1 >= argc) {ret = -1; break;}
				conpo = argv[++i];
				break;
			case 'v': arg_flags |= ARG_VERBOSE; break;
			default: ret = -1;
		}
	}

	return ret;
}

void show_help()
{
	fprintf(stderr,"Usage: %s [OPTION] [OPTION ARGS]\n",argv[0]);
	fprintf(stderr,"Options:\n");
	fprintf(stderr,"\t-h\t\tShow this help\n");
	fprintf(stderr,"\t-c <ip> <port>\tConnect to another user with supplied ip and port\n");
	fprintf(stderr,"\t-w <port>\n");
	fprintf(stderr,"\t-l <port>\tListen on the supplied port for a connection\n");
	return;
}
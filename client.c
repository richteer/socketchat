#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "network.h"

#define ARG_CONNECT (0x1<<1)
#define ARG_LISTEN  (0x1<<2)
#define ARG_VERBOSE (0x1<<3)

#define bail return
#define psi fprintf(stderr,"Received SIGINT, Quitting...\n")
#define psf fprintf(stderr,"Received SIGSEGV, Fix Me...\n")


unsigned arg_flags = 0;
char* conip = NULL;
char* conpo = NULL;


static void cli_send(void);
static void cli_recv(void);

static int handle_args(int,char**);
static void show_help(char*);

static void handle_sigint(int x) { psi; net_close(); exit(0); }
static void handle_sigsegv(int x) { psf; net_close(); exit(1); }
static void handle_sigchld(int x) { while(waitpid(-1, NULL, WNOHANG) > 0); }

int main(int argc, char **argv)
{
	int ret;
    struct sigaction sa;
    pid_t pid;

	if ((argc - 1) && handle_args(argc,argv)) {
		//fprintf("Error parsing arguments\n");
		show_help(argv[0]);
		return 1;
	}

	signal(SIGINT,handle_sigint);
	signal(SIGSEGV,handle_sigsegv);
	
    sa.sa_handler = handle_sigchld; // reap all dead processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

	printf("Client started, hit ^C to exit\n");
	if (arg_flags & ARG_CONNECT) {
		printf("Trying to connect to %s:%s\n",conip,conpo);
		ret = net_connect(conip, conpo);
	} else if (arg_flags & ARG_LISTEN) {
		printf("Waiting for connection...\n");
		ret = net_listen(conpo);
	} else {
		fprintf(stderr,"You must either listen (-w or -l) or connect (-c)\n");
		fprintf(stderr,"See -h for more usage information\n");
		return 2;
	}
	if (ret) {
		fprintf(stderr,"Failed to start networking... error code %d\n",ret);
		return 3;
	}
	printf("Connected!\n");


	if (0 != (pid = fork())) {
		cli_recv();
		printf("recv closed\n");
		kill(pid, SIGKILL);
	}
	else {
		cli_send();
		printf("send closed\n");
		bail 0;
	}

	printf("Connection closed.\n");

	return 0;
}

static void cli_send(void)
{
	net_packet_t pk;

	while (1)
	{
		printf(">>> ");
		fgets(pk.body,255,stdin);
		if (0 == net_send(&pk)) break;
	}

	bail;
}

static void cli_recv(void)
{
	net_packet_t pk;
	while (1) {
		if (0 == net_recv(&pk)) break;
		printf("Message from friend: %s\n",pk.body);
	}

	bail;
}

static int handle_args(int argc, char** argv) 
{
	int i, ret = 0;
	for (i = 1; i < argc; i++) {
		switch(argv[i][1]) {
			case 'h': show_help(argv[0]); exit(2); 	break;
			case 'c': 
				arg_flags |= ARG_CONNECT; 
				if (i+2 >= argc) {ret = -1; break;}
				conip = argv[++i];
				conpo = argv[++i];
				break;
			case 'l':
			case 'w':
				arg_flags |= ARG_LISTEN;
				if (i+1 >= argc) {ret = -1; break;}
				conpo = argv[++i];
				break;
			case 'v': arg_flags |= ARG_VERBOSE; break;
			default: ret = -1;
		}
	}

	if ((arg_flags & ARG_CONNECT) && (arg_flags & ARG_LISTEN)) ret = -2;

	return ret;
}

static void show_help(char* name)
{
	fprintf(stderr,"Usage: %s [OPTION] [OPTION ARGS]\n",(NULL == name)? "client" : name);
	fprintf(stderr,"Options:\n");
	fprintf(stderr,"\t-h\t\tShow this help\n");
	fprintf(stderr,"\t-c <ip> <port>\tConnect to another user with supplied ip and port\n");
	fprintf(stderr,"\t-w <port>\n");
	fprintf(stderr,"\t-l <port>\tListen on the supplied port for a connection\n");
	return;
}
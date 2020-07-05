
#include <sys/un.h>
#include <sys/socket.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define BUF_SIZE 256
#define SV_SOCK_PATH "/tmp/ud_ucase"

int main(int argc, char** argv)
{
	struct sockaddr_un svaddr,claddr;
	int sock,j;
	size_t msgLen;
	ssize_t numBytes;
	char resp[BUF_SIZE];

	if(argc < 2 || strcmp(argv[1], "--help") == 0){
		printf("Usage: %s msg ...\n", argv[0]);
	}

	sock = socket(AF_UNIX, SOCK_DGRAM, 0);
	if(sock == -1){
		printf("socket() error\n"); exit(1);
	}
	memset(&claddr, 0, sizeof(struct sockaddr_un));
	claddr.sun_family = AF_UNIX;


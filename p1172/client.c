
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
	snprintf(claddr.sun_path, sizeof(claddr.sun_path), 
			"/tmp/ud_ucase_cl.%ld", (long)getpid());
	if(bind(sock, (struct sockaddr*)&claddr, sizeof(struct sockaddr_un)) == -1){
		printf("bind() error\n"); exit(1);
	}

	memset(&svaddr, 0, sizeof(struct sockaddr_un));
	svaddr.sun_family = AF_UNIX;
	strncpy(svaddr.sun_path, SV_SOCK_PATH, sizeof(svaddr.sun_path)-1);

	for(j=1;j<argc; j++){
		msgLen = strlen(argv[j]);
		if(sendto(sock, argv[j], msgLen, 0, 
			(struct sockaddr*)&svaddr, 
			sizeof(struct sockaddr_un)) != msgLen){
			printf("sendto() error\n"); exit(1);
		}

		numBytes = recvfrom(sock, resp, BUF_SIZE, 0, NULL, NULL);
		if(numBytes == -1 ){
			printf("recvfrom() error\n"); exit(1);
		}
		printf("Response %d: %.*s\n", j, (int)numBytes, resp);
	}
	remove(claddr.sun_path);
	exit(0);
}

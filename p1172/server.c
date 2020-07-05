#include <sys/un.h>
#include <sys/socket.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define BUF_SIZE 256
#define SV_SOCK_PATH "/tmp/ud_ucase"

int main()
{
	struct sockaddr_un svaddr, claddr;
	int sock, j;
	ssize_t numBytes;
	socklen_t len;
	char buf[BUF_SIZE];
	
	sock = socket(AF_UNIX, SOCK_DGRAM, 0);
	if(sock == -1) {
		printf("socket() error\n");
		exit(1);
	}

	if(strlen(SV_SOCK_PATH) > sizeof(svaddr.sun_path) - 1) {
		printf("Server socket path too long:%s\n", SV_SOCK_PATH);
		exit(1);
	}
	if(remove(SV_SOCK_PATH) == -1 && errno != ENOENT) {
		printf("remove %s\n", SV_SOCK_PATH);
		exit(1);
	}
	memset(&svaddr,0, sizeof(struct sockaddr_un));
	svaddr.sun_family = AF_UNIX;
	strncpy(svaddr.sun_path, SV_SOCK_PATH, sizeof(svaddr.sun_path) - 1);

	if(bind(sock, (struct sockaddr*) &svaddr, sizeof(struct sockaddr_un)) == -1) {
		printf("bind\n");
		exit(1);
	}
	for(;;){
		len = sizeof(struct sockaddr_un);
		numBytes = recvfrom(sock, buf, BUF_SIZE, 0, (struct sockaddr*)&claddr, &len);
		if(numBytes == -1){
			printf("recvfrom()\n");
			exit(1);
		}
		printf("Server received %ld bytes from %s\n", (long)numBytes, claddr.sun_path);

		for(j=0; j<numBytes; j++){
			buf[j] = toupper((unsigned char)buf[j]);
		}
		if(sendto(sock, buf, numBytes, 0, (struct sockaddr*)&claddr, len) != numBytes){
			printf("sendto() error\n");
			exit(1);
		}
	}

	return 0;
}

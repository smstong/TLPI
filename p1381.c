#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char** argv)
{
	int mfd = open("/dev/ptmx", O_RDWR|O_NOCTTY);
	if (mfd == -1){
		printf("error to create a pty master\n");
		exit(1);
	}
	printf("PTY master device file descriptor is:%d\n", mfd);
	sleep(10);
	return 0;
}

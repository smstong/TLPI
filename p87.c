#include <stdio.h>
#include <fcntl.h>
#include <ctype.h>
#include <errno.h>

int main(int argc, char** argv)
{ 
    int n = 0;
    char buf[512];

    int i = 0;
    int out_files[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

    out_files[0] = 1; /* stdout */
    /* create files */
    for(i=1; i<argc; i++) {
	out_files[i] = open(argv[i], O_WRONLY | O_CREAT | O_TRUNC);
	if( out_files[i] == -1) {
	    printf("create %s: %s\n", argv[i], strerror(errno));
	    return -1;
	}
    }

    while( (n = read(0, buf, sizeof(buf))) > 0) {
	for(i=0; i<10; i++) {
	    if(-1 == out_files[i]) continue;
	    if( n != write(out_files[i], buf, n)) {
		perror("write");
		return -1;
	    }
	}
    }	

    if( -1 == n) {
	perror("read");
	return -1;
    }

    for(i=0; i<10; i++) {
	if(out_files[i] != -1) {
	    if(-1 == close(out_files[i])) {
		perror("close");
	    }
	}
    }
    return 0;
}

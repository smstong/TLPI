#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    char* addr;
    int fd;
    struct stat sb;

    if(argc !=2 || strcmp(argv[1], "--help")==0){
        printf("Usage: %s file\n", argv[0]);
        exit(0);
    }

    fd = open(argv[1], O_RDONLY);
    if(-1 == fd){
        perror("open"); exit(1);
    }

    if(fstat(fd, &sb) == -1){
        perror("fstat"); exit(1);
    }

    addr = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if(addr == MAP_FAILED){
        perror("mmap"); exit(1);
    }

    if(write(1, addr, sb.st_size) != sb.st_size){
        perror("write"); exit(1);
    }
    getchar();
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char** argv)
{
    int code = 0;

    if(fork()==0){
        sleep(5);
        _exit(2);
    }

    if(-1 == wait(&code)){
        printf("wait() failed\n");
    }
    printf("%d\n", code);
    return 0;
}

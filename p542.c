#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char** argv)
{
    int code = 0;
    pid_t pid = wait(&code); 

    printf("pid: %d, code: %d\n", pid, code);
    return 0;
}

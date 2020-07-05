#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>

int main(int argc, char** argv)
{
    pthread_t tid = gettid();
    pid_t pid = getpid();

    printf("PID=%ld, TID=%ld\n", pid, tid);
    exit(0);
}

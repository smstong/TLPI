#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/syscall.h>

static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void showIDs(const char* msg)
{
    pthread_mutex_lock(&mtx);
    printf("%s: PID=%ld, TID=%ld, threadID=%ld\n", 
            msg,
            getpid(),
            syscall(SYS_gettid),
            pthread_self()
          );
    pthread_mutex_unlock(&mtx);
}

static void* threadFunc(void* arg)
{
    char* s = (char*)arg;
    int i = 0;
    for (i =0; i<100; i++){
        showIDs("Child");
        sleep(1);
    }
    return (void*)strlen(s);
}

int main(int argc, char** argv)
{
    pthread_t t1;
    void* res;
    int s;

    s = pthread_create(&t1, NULL, threadFunc, "Hello world\n");
    if( s != 0){
        exit(1);
    }

    for(int i=0; i<200; i++){
        showIDs("Parent");
        sleep(1);
    }
    printf("Message from main()\n");

    s = pthread_join(t1, &res);
    if (s != 0){
        exit(1);
    }

    printf("Thread returned %ld\n", (long)res);

    exit(0);
}

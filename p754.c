#include <stdio.h>
#include <sys/resource.h>

void f()
{
    for(int i=0; i<1000000; i++){
        float x = (float)i;
    }
}

int main(int argc, char** argv)
{
    f();
    struct rusage usage;
    int r = getrusage(RUSAGE_SELF, &usage);
    if(r == -1){
        return -1;
    }
    struct timeval utime = usage.ru_utime;
    struct timeval stime = usage.ru_stime;

    printf("user time: %ld s + %ld ms\n", utime.tv_sec, utime.tv_usec);
    printf("sys time: %ld s + %ld ms\n", stime.tv_sec, stime.tv_usec);

    return 0;
}

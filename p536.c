#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static void atexitFunc1(void)
{
    printf("atexti function 1 called\n");
}
static void onexitFunc1(int code, void* arg)
{
    printf("on_exit function called: status = %d, arg=%ld\n",
            code, (long)arg);
}
int main(int argc, char** argv)
{
    if(atexit(atexitFunc1) != 0){
        _exit(1);
    }
    if(on_exit(onexitFunc1, (void*)10) != 0){
        _exit(2);
    }
    exit(2);
}

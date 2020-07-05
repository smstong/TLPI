#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char * argv[])
{
    printf("Hello world\n");
    write(STDOUT_FILENO, "Ciao\n", 5);

    if(fork() == -1)
        _exit(2);

    sleep(10000);
    _exit(0);
    return 0;
}

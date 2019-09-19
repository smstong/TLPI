#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
    int errn = atoi(argv[1]);
    printf("%d: %s\n", errn, strerror(errn));
    return 0;
}

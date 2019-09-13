#include <stdio.h>
#include <gnu/libc-version.h>

int main(int argc, char** argv)
{
    const char * s = NULL;
    s = gnu_get_libc_version();
    printf("%s\n", s);
    return 0;
}

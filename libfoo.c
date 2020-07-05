#include <stdio.h>

static void xyz()
{
    printf("foo::xyz()\n");
}

void f1()
{
    printf("libfoo.so::f1()\n");
    xyz();
}

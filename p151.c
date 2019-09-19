#include <stdio.h>
#include <stdlib.h>

extern char end, etext, edata;
int x = 0;
int main(int argc, char** argv)
{
    char* p = (char*)malloc(1);
    printf("%p\n", p);
    printf("&etext=%p, &edata=%p, &end=%p\n",&etext, &edata,  &end);
    x++;
    return 0;
}

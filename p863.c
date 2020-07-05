#define _GNU_SOURCE 1
#include <stdio.h>
#include <dlfcn.h>
#include <math.h>

int g_x = 99;
void f(float x)
{
    double y = sin(x);
    printf("%f", y);
}

int main(int argc, char** argv)
{
    f(2);
    void* so = dlopen(NULL, RTLD_NOW | RTLD_GLOBAL);
    void* p = dlsym(so, "sin");
    printf("ERROR:%s\n", dlerror());
    printf("&g_x = %p, addr = %p\n", f, p);

    typedef double (*SIN)(double);

    SIN mysin = (SIN)p;

    printf("%f\n", mysin(0.3));

    char fname[256];
    char sname[256];
    Dl_info di = {
        fname,
        NULL,
        sname,
        NULL,
    };

    dladdr(p, &di);
    printf("%s, %s\n", di.dli_fname, di.dli_sname);
    return 0;
}

#include <unistd.h>
void start()
{
    write(0, "hello mod1\n", 11);
    _exit(0);
}

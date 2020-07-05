#include <stdio.h>
#include <unistd.h>
#include <crypt.h>

int main(int argc, char* argv[])
{
    char* p = crypt("test123","$6$9qa56AqqXIMjnrN/$");
    if (p) {
	printf("%s\n", p);
    }
    return 0;
}



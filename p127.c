#include <stdio.h>

extern char **environ;
int main(int argc, char** argv)
{
   char** p = NULL;
   for(p = environ; *p; p++){
       puts(*p);
   }
   printf("\n");
   printf("%p\n", &environ);
   printf("%p\n", environ[0]);
   return 0;
}

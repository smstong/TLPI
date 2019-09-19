#include <stdio.h>
int main(int argc, char** argv)
{
    FILE* fp = tmpfile();
    if (NULL == fp){
	return 1;
    }
    fclose(fp);
    return 0;
}

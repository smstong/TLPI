#include <elf.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <signal.h>

char code[] = {0x55,0x48,0x89,0xe5,0x89,0x7d,0xfc,0x48,
    0x89,0x75,0xf0,0xb8,0x2a,0x00,0x00,0x00,0xc9,0xc3,0x00};

void* alloc_ex_memory(int fd)
{
    struct stat s;
    fstat(fd, &s);
    printf("file size: %d\n", s.st_size);
    void* ptr = mmap(0, s.st_size, PROT_READ | PROT_WRITE | PROT_EXEC, 
            MAP_PRIVATE , fd, 0);
    
    ptr += 0x8c60;

    char* p = ptr;
    for(int i=0; i<sizeof(code); i++){
        printf("%2x=%2x ", *(p+i), code[i]);
    }
    printf("\n");

    if(ptr == (void*)-1){
        perror("mmap");
        return NULL;
    }

    return ptr;
}

void* load_ex_file(const char* elfFile)
{
    Elf64_Ehdr header;
    void* ptr;
    int fd = open(elfFile, O_RDONLY);
    if(fd){
        if(1){
            ptr = alloc_ex_memory(fd);
            ptr += 0;
        }else{
            ptr = NULL;
        }
        close(fd);
        return ptr;
    }
    return NULL;
}

typedef void (*STARTFUNC)(const char*, int len);
typedef int (*EXIT)();

int f()
{
    return 9;
}

int myexit()
{
    _exit(1);
}

void signalHandler(int s)
{
    printf("dad\n");
    _exit(1);
}

int main(int argc, char** argv)
{
    signal(SIGSEGV, signalHandler);
    void* p = load_ex_file("mod2.elf");
    printf("fucntion address: %p\n", p);
    EXIT f = (EXIT)p;
    printf("%p\n", f);

    int r = 0;
    r = f();
    printf("%d\n", r);
    return 0;
}

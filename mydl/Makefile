all: mod2.elf loader

mod2.elf: mod2.o
	gcc -Wl,-emain -static-pie -o mod2.elf mod2.o

mod2.o: mod2.c
	gcc -c -fpie -o mod2.o  mod2.c

loader: loader.c
	gcc -c -fpic -o loader.o loader.c
	gcc -z execstack -fpic -o $@ $<


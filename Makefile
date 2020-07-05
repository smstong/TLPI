all: ./bin/*
./bin/p163: p163.c
	gcc --std=c99 -lcrypt -o $@ $<
	ln -sf $@ test
./bin/% : %.c
	gcc --std=c99 -o $@ $<
	ln -sf $@ test

all: ./bin/*
./bin/% : %.c
	gcc --std=c99 -o $@ $<
	ln -sf $@ test

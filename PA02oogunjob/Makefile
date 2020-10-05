WARNING = -Wall -Wshadow -pedantic
ERROR = -Wvla
GCC = gcc -std=c99 -g -O3 $(WARNING) $(ERROR)
VAL = valgrind --tool=memcheck --log-file=memcheck.txt --leak-check=full --verbose

SRCS = pa2.c huffman.c
OBJS = $(SRCS:%.c=%.o)

pa2: $(OBJS)
	 $(GCC) $(TESTFLAGS) $(OBJS) -o pa2

.c.o:
	$(GCC) $(TESTFLAGS) -c $*.c

testmemory: pa2
	$(VAL) ./pa2 encoded/gophers_huff.hbt gophers.tree gophers.ori gophers.count gophers.htree gophers.eval

testall: gophers lorum stone woods binary1

gophers: pa2
	./pa2 encoded/gophers_huff.hbt gophers.tree gophers.ori gophers.count gophers.htree gophers.eval

lorum: pa2
	./pa2 encoded/lorum_huff.hbt lorum.tree lorum.ori lorum.count lorum.htree lorum.eval

stone: pa2
	./pa2 encoded/stone_huff.hbt stone.tree stone.ori stone.count stone.htree stone.eval

woods: pa2
	./pa2 encoded/woods_huff.hbt woods.tree woods.ori woods.count woods.htree woods.eval

binary1: pa2
	./pa2 encoded/binary1_huff.hbt binary1.tree binary1.ori binary1.count binary1.htree binary1.eval

clean: # remove all machine generated files
	rm -f pa2 *.o output?

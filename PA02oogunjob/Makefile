WARNING = -Wall -Wshadow -pedantic
ERROR = -Wvla
GCC = gcc -std=c99 -g -O3 $(WARNING) $(ERROR) $(LIBS)
LIBS = -lm
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
	diff -w gophers.tree tree/gophers_huff.tree
	diff -w gophers.ori decoded/gophers
	diff -w gophers.count count/gophers.count

lorum: pa2
	./pa2 encoded/lorum_huff.hbt lorum.tree lorum.ori lorum.count lorum.htree lorum.eval
	diff -w lorum.tree tree/lorum_huff.tree
	diff -w lorum.ori decoded/lorum
	diff -w lorum.count count/lorum.count

stone: pa2
	./pa2 encoded/stone_huff.hbt stone.tree stone.ori stone.count stone.htree stone.eval
	diff -w stone.tree tree/stone_huff.tree
	diff -w stone.ori decoded/stone
	diff -w stone.count count/stone.count

woods: pa2
	./pa2 encoded/woods_huff.hbt woods.tree woods.ori woods.count woods.htree woods.eval
	diff -w woods.tree tree/woods_huff.tree
	diff -w woods.ori decoded/woods
	diff -w woods.count count/woods.count

binary1: pa2
	./pa2 encoded/binary1_huff.hbt binary1.tree binary1.ori binary1.count binary1.htree binary1.eval
	diff -w binary1.tree tree/binary1_huff.tree
	diff -w binary1.ori decoded/binary1
	diff -w binary1.count count/binary1.count

clean: # remove all machine generated files
	rm -f pa2 *.o output?

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
	$(VAL) ./pa2 -a 0.b output0a

testall: test1 test2 test3 test4 test5 test6

test1: pa2
	./pa2 -a 15.b output1a
	diff -w output1a 15sa.b

clean: # remove all machine generated files
	rm -f pa2 *.o output?

WARNING = -Wall -Wshadow -pedantic
ERROR = -Wvla
GCC = gcc -std=c99 -g -O3 $(WARNING) $(ERROR)
VAL = valgrind --tool=memcheck --log-file=memcheck.txt --leak-check=full --verbose

SRCS = pa4.c
OBJS = $(SRCS:%.c=%.o)

pa4: $(OBJS)
	 $(GCC) $(TESTFLAGS) $(OBJS) -o pa4

.c.o:
	$(GCC) $(TESTFLAGS) -c $*.c

testmemory: pa4
	$(VAL) ./pa4 -b examples/inputs/ops0.b tree0.b

testall: 3 5 10 100 1000

ops0: pa4
	./pa4 -b examples/inputs/ops0.b tree0.b
    ./pa4 -e tree0.b 

ops1: pa4
	./pa4 -b examples/inputs/ops1.b tree1.b
    ./pa4 -e tree1.b

clean: # remove all machine generated files
	rm -f pa4 *.o output?

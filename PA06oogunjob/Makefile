WARNING = -Wall -Wshadow -pedantic
ERROR = -Wvla
GCC = gcc -std=c99 -g -O3 $(WARNING) $(ERROR)
VAL = valgrind --tool=memcheck --log-file=memcheck.txt --leak-check=full --verbose

SRCS = pa6.c 
OBJS = $(SRCS:%.c=%.o)

pa6: $(OBJS)
	 $(GCC) $(TESTFLAGS) $(OBJS) -o pa6

.c.o:
	$(GCC) $(TESTFLAGS) -c $*.c

testmemory: pa6
	$(VAL) ./pa6 -e examples/tree0.b

testall: ops0 ops1 ops2 ops3

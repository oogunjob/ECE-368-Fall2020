WARNING = -Wall -Wshadow -pedantic
ERROR = -Wvla
GCC = gcc -std=c99 -g -O3 $(WARNING) $(ERROR)
VAL = valgrind --tool=memcheck --log-file=memcheck.txt --leak-check=full --verbose

SRCS = pa6.c evaluate.c
OBJS = $(SRCS:%.c=%.o)

pa6: $(OBJS)
	 $(GCC) $(TESTFLAGS) $(OBJS) -o pa6

.c.o:
	$(GCC) $(TESTFLAGS) -c $*.c

testmemory: pa6
	$(VAL) ./pa6 -e examples/4_4.b examples/4_4.s


testall: 4x4

4x4: pa6
	./pa6 -e examples/4_4.b examples/4_4.s



clean: # remove all machine generated files
	rm -f pa6 *.o output?

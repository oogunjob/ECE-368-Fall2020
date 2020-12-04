WARNING = -Wall -Wshadow -pedantic
ERROR = -Wvla
GCC = gcc -std=c99 -g -O3 $(WARNING) $(ERROR)
VAL = valgrind --tool=memcheck --log-file=memcheck.txt --leak-check=full --verbose

SRCS = pa6.c evaluate.c sequence.c
OBJS = $(SRCS:%.c=%.o)

pa6: $(OBJS)
	 $(GCC) $(TESTFLAGS) $(OBJS) -o pa6

.c.o:
	$(GCC) $(TESTFLAGS) -c $*.c

testmemory: pa6
	$(VAL) ./pa6 -s examples/4_5.b 4_5.t 4_5.s


testall: 4x4 4x5 5x5 10x10

test1: pa6
	./pa6 -s examples/4_4.b 4_4.t 4_4.s
	diff 4_4.t examples/4_4.t

test2: pa6
	./pa6 -s examples/4_5.b 4_5.t 4_5.s
	diff 4_5.t examples/4_5.t

test3: pa6
	./pa6 -s examples/5_5.b 5_5.t 5_5.s
	diff 5_5.t examples/5_5.t

test4: pa6
	./pa6 -s examples/10_10.b 10_10.t 10_10.s
	diff 10_10.t examples/10_10.t

4x4: pa6
	./pa6 -e examples/4_4.b examples/4_4.s

4x5: pa6
	./pa6 -e examples/4_5.b examples/4_5.s

5x5: pa6
	./pa6 -e examples/5_5.b examples/5_5.s

10x10: pa6
	./pa6 -e examples/10_10.b examples/10_10.s

clean: # remove all machine generated files
	rm -f pa6 *.o output?

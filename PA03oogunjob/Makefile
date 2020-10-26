WARNING = -Wall -Wshadow -pedantic
ERROR = -Wvla
GCC = gcc -std=c99 -g -O3 $(WARNING) $(ERROR)
VAL = valgrind --tool=memcheck --log-file=memcheck.txt --leak-check=full --verbose

SRCS = pa3.c delay.c
OBJS = $(SRCS:%.c=%.o)

pa3: $(OBJS)
	 $(GCC) $(TESTFLAGS) $(OBJS) -o pa3

.c.o:
	$(GCC) $(TESTFLAGS) -c $*.c

testmemory: pa3
	$(VAL) ./pa3 examples/inputs/3.txt 3.pre 3.rc 3.tcap 3.delay

testall: 0 3 5 10 100 1000

0: pa3
	./pa3 examples/inputs/0.txt 0.pre 0.rc 0.tcap 0.delay

3: pa3
	./pa3 examples/inputs/3.txt 3.pre 3.rc 3.tcap 3.delay
	diff -w 3.pre examples/solutions/preorder/3.pre
	diff -w 3.rc examples/solutions/resistance_capacitance/3.rc
	diff -w 3.tcap examples/solutions/totalcapacitance/3.tcap

5: pa3
	./pa3 examples/inputs/5.txt 5.pre 5.rc 5.tcap 5.delay
	diff -w 5.pre examples/solutions/preorder/5.pre
	diff -w 5.rc examples/solutions/resistance_capacitance/5.rc
	diff -w 5.tcap examples/solutions/totalcapacitance/5.tcap
	diff -w 5.delay examples/solutions/delay/5.delay
	
10: pa3
	./pa3 examples/inputs/10.txt 10.pre 10.rc 10.tcap 10.delay

100: pa3
	./pa3 examples/inputs/100.txt 100.pre 100.rc 100.tcap 100.delay

1000: pa3
	./pa3 examples/inputs/1000.txt 1000.pre 1000.rc 1000.tcap 1000.delay

clean: # remove all machine generated files
	rm -f pa3 *.o output?
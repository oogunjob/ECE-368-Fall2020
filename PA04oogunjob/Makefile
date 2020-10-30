WARNING = -Wall -Wshadow -pedantic
ERROR = -Wvla
GCC = gcc -std=c99 -g -O3 $(WARNING) $(ERROR)
VAL = valgrind --tool=memcheck --log-file=memcheck.txt --leak-check=full --verbose

SRCS = pa4.c build.c evaluate.c
OBJS = $(SRCS:%.c=%.o)

pa4: $(OBJS)
	 $(GCC) $(TESTFLAGS) $(OBJS) -o pa4

.c.o:
	$(GCC) $(TESTFLAGS) -c $*.c

testmemory: pa4
	$(VAL) ./pa4 -e examples/tree0.b

testbuild: ops0 ops1 ops2 ops3

testevaluate: tree0 tree1 tree2 tree3 invalidtree0 invalidtree1 invalidtree2

invalid: pa4
	./pa4 -a input output

ops0: pa4
	./pa4 -b examples/ops0.b tree0.b
	diff -w tree0.b examples/tree0.b

ops1: pa4
	./pa4 -b examples/ops1.b tree1.b
	diff -w tree1.b examples/tree1.b

ops2: pa4
	./pa4 -b examples/ops2.b tree2.b
	diff -w tree2.b examples/tree2.b

ops3: pa4
	./pa4 -b examples/ops3.b tree3.b
	diff -w tree3.b examples/tree3.b

tree0: pa4
	./pa4 -e examples/tree0.b

tree1: pa4
	./pa4 -e examples/tree1.b

tree2: pa4
	./pa4 -e examples/tree2.b

tree3: pa4
	./pa4 -e examples/tree3.b

invalidtree0: pa4
	./pa4 -e examples/invalidtree0.b

invalidtree1: pa4
	./pa4 -e examples/invalidtree1.b

invalidtree2: pa4
	./pa4 -e examples/invalidtree1.b

clean: # remove all machine generated files
	rm -f pa4 *.o output?

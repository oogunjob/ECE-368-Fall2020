WARNING = -Wall -Wshadow -pedantic
ERROR = -Wvla
GCC = gcc -std=c99 -g -O3 $(WARNING) $(ERROR)
VAL = valgrind --tool=memcheck --log-file=memcheck.txt --leak-check=full --verbose

SRCS = pa1.c sequence.c shell_array.c shell_list.c 
OBJS = $(SRCS:%.c=%.o)

pa1: $(OBJS)
	 $(GCC) $(TESTFLAGS) $(OBJS) -o pa1

.c.o:
	$(GCC) $(TESTFLAGS) -c $*.c

testmemory: pa1
	$(VAL) ./pa1 -l 100K.b output1l

testall: test1 test2 test3 test4 test5

test1: pa1
	./pa1 -a 15.b output1a
	diff -w output1a 15sa.b

	./pa1 -l 15.b output1l
	diff -w output1l 15sl.b

test2: pa1
	./pa1 -a 1K.b output2a
	diff -w output2a 1Ksa.b

	./pa1 -l 1K.b output2l
	diff -w output2l 1Ksl.b	

test3: pa1
	./pa1 -a 10K.b output3a

	./pa1 -l 10K.b output3l

test4: pa1
	./pa1 -a 100K.b output4a

	./pa1 -l 100K.b output4l

test5: pa1
	./pa1 -a 1M.b output5a

	./pa1 -l 1M.b outputla

clean: # remove all machine generated files
	rm -f pa1 *.o output?

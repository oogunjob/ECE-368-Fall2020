WARNING = -Wall -Wshadow -pedantic
ERROR = -Wvla
GCC = gcc -std=c99 -g -O3 $(WARNING) $(ERROR)
VAL = valgrind --tool=memcheck --log-file=memcheck.txt --leak-check=full --verbose

SRCS = pa1.c shell_array.c shell_list.c sequence.c
OBJS = $(SRCS:%.c=%.o)

pa1: $(OBJS)
	 $(GCC) $(TESTFLAGS) $(OBJS) -o pa1

.c.o:
	$(GCC) $(TESTFLAGS) -c $*.c

testmemory: pa1
	$(VAL) ./pa1 -a 15.b output1a

testall: test1 test2 test3 test4 test5

test1: pa1
	./pa1 -a 15.b output1a
	# diff -w output1a 15sa.b

test2: pa1
	./pa1 -a 1K.b output2a
	# diff -w output2a examples/1Ksa.b
	
	# ./pa1 -l examples/1K.b output2l
	# diff -w output2l examples/1Ksl.b	

test3: pa1
	./pa1 -a 10K.b output3a
	#diff -w output3a examples/10Ksa.b
	
	# ./pa1 -l 10K.b output3l
	#diff -w output3l examples/10Ksl.b
	
test4: pa1
	./pa1 -a 100K.b output4a
	#diff -w output4a examples/100Ksa.b
	
	# ./pa1 -l 100K.b output4l
	#diff -w output4l examples/100Ksl.b

test5: pa1
	./pa1 -a 1M.b output5a
	#diff -w output5a examples/1Msa.b
	
	./pa1 -l 1M.b output5l
	#diff -w output5l examples/1Msl.b

clean: # remove all machine generated files
	rm -f pa1 *.o output?

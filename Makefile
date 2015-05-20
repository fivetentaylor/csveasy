CC=clang
CFLAGS=-I. -O3
DEPS = 
OBJ = main.o hash.o
TEST_OBJ = test_main.o test_list.o list.o

%.o : %.c %.h $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hsv : $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

test_hsv : $(TEST_OBJ)
	gcc -o $@ $^ $(CFLAGS)

clean : 
	rm *.o

data.txt : mk_test_data.sh
	./mk_test_data.sh > data.txt


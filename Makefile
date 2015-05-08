CC=clang
CFLAGS=-I. -O3
DEPS = 
OBJ = main.o hash.o

%.o : %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

csv_easy : $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

clean : 
	rm *.o

data.txt : mk_test_data.sh
	./mk_test_data.sh > data.txt


CC= g++
CFLAGS= -O3

all:
	$(CC) $(CFLAGS) baseenc.cpp -o main.out
	$(CC) $(CFLAGS) encode11.cpp -o main2.out

clean:
	rm -f *.exe *.out *.o

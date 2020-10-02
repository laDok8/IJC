CC = gcc
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra -lm 
PROGRAMS = steg-decode primes primes-i

all: $(PROGRAMS)

steg-decode: steg-decode.o eratosthenes.o error.o ppm.o bitset.o
	$(CC) $(CFLAGS) -o $@ $^

primes: primes.o error.o eratosthenes.o bitset.o
	$(CC) $(CFLAGS) -o $@ $^
primes-i: primes.o eratosthenes.o error.o bitset.o
	$(CC) $(CFLAGS) -DUSE_INLINE -o $@ $^

clean:
	rm -f $(PROGRAMS) *.o
run:
	 ./primes
	 ./primes-i

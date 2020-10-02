// primes.c
// Řešení IJC-DU1, příklad a), 18.3.2020
// Autor: Ladislav Dokoupil, FIT
// Přeloženo: gcc 9.2.1
// vypis poslednich 10 prvocisel pred N(500.000.000) vzestupne

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bitset.h"
#include "eratosthenes.h"

#define N 500000000

int main() {
	clock_t start = clock();
    //bitset_alloc(pole,N);
    bitset_create(pole,N);
    eratosthenes(pole);
	int pom=0;
	unsigned long buffer[10];
	for(unsigned long i=bitset_size(pole);i>=2 && pom<10;i--){
		if (!bitset_getbit(pole, i)) {
			buffer[pom] = i;
			pom++;
		}
	}
	for (int j = pom-1; j >= 0; j--)
		printf("%ld\n",buffer[j]);

	fprintf(stderr, "Time=%.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC);
	return 0;
}

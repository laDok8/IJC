// eratosthenes.c
// Řešení IJC-DU1, příklad a), 18.3.2020
// Autor: Ladislav Dokoupil, FIT
// Přeloženo: gcc 9.2.1

#include "bitset.h"
#include "eratosthenes.h"

void eratosthenes(bitset_t pole){
	long unsigned size = bitset_size(pole);
    long unsigned rt = sqrt(size);

    for(long unsigned i=2;i<=rt;i++){
        if(!bitset_getbit(pole,i)){
            for (long unsigned j = i*2; j <= size; j+=i) {
                bitset_setbit(pole,j,1);//1 - neni prime
            }
        }
    }
}


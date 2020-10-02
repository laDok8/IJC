// steg-decode.c
// Řešení IJC-DU1, příklad a), 18.3.2020
// Autor: Ladislav Dokoupil, FIT
// Přeloženo: gcc 9.2.1
//desifruje ulozenou zpravu z ppm obrazku v argumentech.
//data jsou ulozena na nejnizsim bitu dat s indexem prvocisel

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <ctype.h>
#include "bitset.h"
#include "eratosthenes.h"
#include "ppm.h"

int main(int argc,char **argv) {
	if(argc != 2)
		error_exit("Nedostatek argumentu");
	setlocale(LC_ALL, "cs_CZ.utf8");
    struct ppm* img = ppm_read(argv[1]);
    if(img == NULL){
		return 1;
    }
    unsigned vel = img->xsize*img->ysize*3;
	bitset_alloc(pole,vel);
    eratosthenes(pole);
    int shift=0;
	unsigned char c=0;

    for(unsigned long i=23;i<=vel;i++){
        if(!bitset_getbit(pole,i)){
            int x = (img->data[i] & 1)>0;
            c += x<<shift;
            shift++;
        }
        if(shift>=8){
			printf("%c",c);
			if(c==0)
				break;
            shift=0;c=0;
        }
    }
	printf("\n");
    bitset_free(pole);
    ppm_free(img);
    return 0;
}

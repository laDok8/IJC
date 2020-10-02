// bitset.h
// Řešení IJC-DU1, příklad a), 18.3.2020
// Autor: Ladislav Dokoupil, FIT
// Přeloženo: gcc 9.2.1

#ifndef BITSET_H
#define BITSET_H


#include<math.h>
#include<limits.h>
#include <assert.h>
#include "error.h"

typedef unsigned long *bitset_t;
typedef unsigned long bitset_index_t;

//#define bitset_create(jmeno_pole,velikost) unsigned long jmeno_pole [(int)(ceil((velikost+1)/(float)(CHAR_BIT*sizeof(unsigned long)))+1)] = {velikost,0}
#define bitset_create(jmeno_pole,velikost) unsigned long jmeno_pole [(velikost+1)/(CHAR_BIT*sizeof(unsigned long))+1+(((velikost+1)%(CHAR_BIT*sizeof(unsigned long))==0)?0:1)] = {velikost,0};\
static_assert(velikost>0, "bitset_create: Chyba velikosti")


#define bitset_alloc(jmeno_pole,velikost) bitset_t jmeno_pole = calloc(((int)ceil((velikost+1)/(float)(CHAR_BIT*sizeof(unsigned long)))+1), sizeof(unsigned long));\
jmeno_pole[0]=velikost;\
assert((jmeno_pole != NULL) && velikost > 0&&"bitset_alloc: Chyba alokace paměti")

#ifndef USE_INLINE

	#define bitset_free(jmeno_pole)free(jmeno_pole)

	#define bitset_size(jmeno_pole)jmeno_pole[0]

    #define bitset_setbit(jmeno_pole,index,vyraz)do{\
    	if(index > bitset_size(jmeno_pole)) error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu",(unsigned long)index, (unsigned long)bitset_size(jmeno_pole)); \
    	if(vyraz)\
    	    jmeno_pole[index/(sizeof(unsigned long)*CHAR_BIT)+1] |= 1L<<(index%(sizeof(unsigned long)*CHAR_BIT));\
        else\
            jmeno_pole[index/(sizeof(unsigned long)*CHAR_BIT)+1] &= ~(1L<<(index%(sizeof(unsigned long)*CHAR_BIT)));\
    }while(0);

     #define bitset_getbit(jmeno_pole,index) (index <= bitset_size(jmeno_pole)?((jmeno_pole[index/(sizeof(unsigned long)*CHAR_BIT)+1] & 1L<<(index%(sizeof(unsigned long)*CHAR_BIT)))? 1:0):\
     (error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu",(unsigned long)index, (unsigned long)bitset_size(jmeno_pole)),-1))

#endif /* !USE_INLINE*/


#ifdef USE_INLINE
inline void bitset_free(bitset_t jmeno_pole){
		free(jmeno_pole);
}

inline unsigned long bitset_size(bitset_t jmeno_pole){
	return jmeno_pole[0];
}

inline void bitset_setbit(bitset_t jmeno_pole,bitset_index_t index,int vyraz){
	if(index > bitset_size(jmeno_pole)) exit(1);
	if(vyraz)\
        jmeno_pole[index/(sizeof(unsigned long)*CHAR_BIT)+1] |= 1L<<(index%(sizeof(unsigned long)*CHAR_BIT));
    else
        jmeno_pole[index/(sizeof(unsigned long)*CHAR_BIT)+1] &= ~(1L<<(index%(sizeof(unsigned long)*CHAR_BIT)));
}

inline int bitset_getbit(bitset_t jmeno_pole,bitset_index_t index){
	if(index > bitset_size(jmeno_pole)){
		error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu",(unsigned long)index, (unsigned long)bitset_size(jmeno_pole));
		return -1;
	}
	if(jmeno_pole[index/(sizeof(unsigned long)*CHAR_BIT)+1] & 1L<<(index%(sizeof(unsigned long)*CHAR_BIT)))
		return 1;
	else
		return 0;
}


#endif /* USE_INLINE*/

#endif /* BITSET_H*/
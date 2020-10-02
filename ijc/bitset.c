// bitset.h
// Řešení IJC-DU1, příklad a), 18.3.2020
// Autor: Ladislav Dokoupil, FIT
// Přeloženo: gcc 9.2.1
#include "bitset.h"

#ifdef USE_INLINE
extern void bitset_free(bitset_t jmeno_pole);
extern unsigned long bitset_size(bitset_t jmeno_pole);
extern void bitset_setbit(bitset_t jmeno_pole,bitset_index_t index,int vyraz);
extern int bitset_getbit(bitset_t jmeno_pole,bitset_index_t index);
#endif /* USE_INLINE*/


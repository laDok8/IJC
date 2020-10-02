// Řešení IJC-DU2, příklad b), 19.4.2020
// Autor: Ladislav Dokoupil, FIT
// Přeloženo: gcc 9.3
#include "htab.h"
#include "htab_struct.h"


size_t htab_bucket_count(const htab_t * t){
	return t->arr_size;
}     // velikost pole
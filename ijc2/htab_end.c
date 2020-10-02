// Řešení IJC-DU2, příklad b), 19.4.2020
// Autor: Ladislav Dokoupil, FIT
// Přeloženo: gcc 9.3

#include "htab.h"
#include "htab_struct.h"


htab_iterator_t htab_end(const htab_t * t){
	htab_iterator_t it = {NULL,t,t->arr_size};
	return it;
}    // iterátor _za_ poslední záznam (id = arr_size)
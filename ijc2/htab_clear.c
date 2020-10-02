// Řešení IJC-DU2, příklad b), 19.4.2020
// Autor: Ladislav Dokoupil, FIT
// Přeloženo: gcc 9.3
#include "htab.h"
#include <stdlib.h>
#include "htab_struct.h"

void htab_clear(htab_t * t){
	for(htab_iterator_t it = htab_begin(t), next = it; !htab_iterator_equal(it,htab_end(it.t)); it = next){
		next = htab_iterator_next(it);
		free((char*) it.ptr->key);
		free(it.ptr);
	}

}

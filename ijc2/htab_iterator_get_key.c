// Řešení IJC-DU2, příklad b), 19.4.2020
// Autor: Ladislav Dokoupil, FIT
// Přeloženo: gcc 9.3

#include "htab.h"
#include "htab_struct.h"

htab_key_t htab_iterator_get_key(htab_iterator_t it){
	return  it.ptr->key;
}

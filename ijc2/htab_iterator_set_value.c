// Řešení IJC-DU2, příklad b), 19.4.2020
// Autor: Ladislav Dokoupil, FIT
// Přeloženo: gcc 9.3

#include "htab.h"
#include "htab_struct.h"

htab_value_t htab_iterator_set_value(htab_iterator_t it, htab_value_t val){
	it.ptr->data = val;
	return it.ptr->data;
}
// Řešení IJC-DU2, příklad b), 19.4.2020
// Autor: Ladislav Dokoupil, FIT
// Přeloženo: gcc 9.3
#include "htab.h"
#include "htab_struct.h"

htab_iterator_t htab_find(htab_t * t, htab_key_t key){

	htab_iterator_t iter = {t->ptr[htab_hash_fun(key) % t->arr_size], t, htab_hash_fun(key) % t->arr_size};
	do{
		if(iter.ptr == NULL){
			break;
		}
		if(strcmp(key,htab_iterator_get_key(iter))==0)
			return iter;
		iter.ptr = iter.ptr->next;
	}while(!htab_iterator_equal(iter,htab_end(t)));
	return iter;
}
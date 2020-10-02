// Řešení IJC-DU2, příklad b), 19.4.2020
// Autor: Ladislav Dokoupil, FIT
// Přeloženo: gcc 9.3

#include "htab.h"
#include "htab_struct.h"

htab_iterator_t htab_iterator_next(htab_iterator_t it){
	do{
		if(it.ptr != NULL && it.ptr->next != NULL) {
			it.ptr = it.ptr->next;
			break;
		}
		else{
			if((it.idx + 1) >= htab_bucket_count(it.t))
				return htab_end(it.t);
			it.idx++;
			it.ptr = it.t->ptr[it.idx];
			if(it.ptr != NULL) {
				break;
			}
		}
	}while(1);
	return it;
}
// iterátor++ (pres cele pole)
// Řešení IJC-DU2, příklad b), 19.4.2020
// Autor: Ladislav Dokoupil, FIT
// Přeloženo: gcc 9.3
#include "htab.h"
#include <stdlib.h>
#include "htab_struct.h"

void htab_erase(htab_t * t, htab_iterator_t it){
	htab_iterator_t find = {t->ptr[it.idx],t,it.idx};
	// first
	if(find.ptr == it.ptr){
		t->ptr[it.idx] = it.ptr->next;
	}
	else{
		//zaznam pred smazanym
		do{
			htab_iterator_next(find);
		}while(find.ptr->next != it.ptr);
		find.ptr->next = it.ptr->next;
	}
	free((char*) it.ptr->key);
	free(it.ptr);
	t->size--;
}

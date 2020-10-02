// Řešení IJC-DU2, příklad b), 19.4.2020
// Autor: Ladislav Dokoupil, FIT
// Přeloženo: gcc 9.3

#include "htab.h"
#include "htab_struct.h"

htab_iterator_t htab_begin(const htab_t* t){
	htab_iterator_t it={NULL,t,0};
	for(int i=0;i<t->arr_size;i++){
		if(t->ptr[i] != NULL){
			it.ptr = t->ptr[i];
			it.idx=i;
			break;
		}
	}
	//empty
	if(it.ptr == NULL){
		return htab_end(t);
	}
	return it;
}  // iterátor na první záznam
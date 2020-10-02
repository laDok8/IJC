// Řešení IJC-DU2, příklad b), 19.4.2020
// Autor: Ladislav Dokoupil, FIT
// Přeloženo: gcc 9.3

#include "htab.h"
#include "htab_struct.h"
#include <stdlib.h>

htab_iterator_t htab_lookup_add(htab_t * t, htab_key_t key){
	htab_iterator_t iter = {t->ptr[htab_hash_fun(key) % t->arr_size], t, htab_hash_fun(key) % t->arr_size};
	int val;
	do{
		if(iter.ptr == NULL)
			break;
		//exist
		if(strcmp(htab_iterator_get_key(iter),key)==0){
			val = htab_iterator_get_value(iter);
			htab_iterator_set_value(iter,++val);
			return iter;
		}
		if(iter.ptr->next == NULL)
			break;
		iter.ptr = iter.ptr->next;
	}while(1);
	//doesnt exist
	char *key1 = calloc(sizeof(char),127);
	if(key1 == NULL)
		return htab_end(t);
	strcpy(key1,key);
	struct htab_item *item = malloc(sizeof(struct htab_item)+127*sizeof(char*));//127 limit
	if(item == NULL)
		return htab_end(t);
	item->next = NULL;
	item->data = 1;
	item->key = key1;
	t->size++;

	//sequence
	if(iter.ptr != NULL){
		iter.ptr->next = item;
		return iter;
	}

	//first
	t->ptr[htab_hash_fun(key) % t->arr_size]=item;
	return iter;
}

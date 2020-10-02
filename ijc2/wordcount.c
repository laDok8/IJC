//
// Created by zen on 3/20/20.
//
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "io.h"
#include "htab.h"

#ifdef HASHTEST
size_t htab_hash_fun(htab_key_t str){
	uint32_t h=0;
	const unsigned char *p;
	for(p=(const unsigned char*)str; *p!='\0'; p++)
		h = 9973*h + *p;
	return h;
}
#endif

int main(){
	int LIMIT = 127;
	char load[LIMIT];
	for(int i = 0; i < LIMIT; i++)
		load[i] = 0;
	htab_t *table = htab_init(9973);
	//testoval jsem rychlost nad slovnikem(65 000slov)
	//nad touto hranici jsem nevidel benefit v rychlosti
	if(table == NULL){
		fprintf(stderr,"htab_init: error");
		return 1;
	}
	while(get_word(load,LIMIT,stdin) != EOF){
		htab_iterator_t t = htab_lookup_add(table,load);
		if(htab_iterator_equal(t,htab_end(table))){
			fprintf(stderr,"lookup_add: error");
			return 1;
		}
	}
	//printf("size: %ld  ar: %ld\n",htab_size(table),htab_bucket_count(table));

	for(htab_iterator_t iter = htab_begin(table); !htab_iterator_equal(iter,htab_end(table)); iter = htab_iterator_next(iter))
		printf("%s\t%d\n",htab_iterator_get_key(iter),htab_iterator_get_value(iter));

	htab_clear(table);
	htab_free(table);
	return 0;
}

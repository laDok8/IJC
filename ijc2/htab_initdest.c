// Řešení IJC-DU2, příklad b), 19.4.2020
// Autor: Ladislav Dokoupil, FIT
// Přeloženo: gcc 9.3
#include "htab.h"
#include <stdlib.h>
#include "htab_struct.h"

// funkce pro práci s tabulkou:
htab_t *htab_init(size_t n){
	htab_t *table = malloc(sizeof(struct htab_item*)*n + sizeof(htab_t));
	if(table == NULL)
		return NULL;

	table->arr_size = n;
	table->size = 0;
	for (long unsigned i = 0; i < n; ++i)
		table->ptr[i] = NULL;
	return table;
}

void htab_free(htab_t * t){
	free(t);
}    // destruktor tabulky

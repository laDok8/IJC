// Řešení IJC-DU2, příklad b), 19.4.2020
// Autor: Ladislav Dokoupil, FIT
// Přeloženo: gcc 9.3

#ifndef IJC2_HTAB_STRUCT_H
#define IJC2_HTAB_STRUCT_H

#include "htab.h"

struct htab_item{
	htab_key_t key;
	int data;
	struct htab_item *next;
};
struct htab{
	int size;
	int arr_size;
	struct htab_item *ptr[];
};
#endif //IJC2_HTAB_STRUCT_H

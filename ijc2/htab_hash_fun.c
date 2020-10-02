// Řešení IJC-DU2, příklad b), 19.4.2020
// Autor: Ladislav Dokoupil, FIT
// Přeloženo: gcc 9.3
#include "htab.h"
#include <stdint.h>
#include "htab_struct.h"

size_t htab_hash_fun(htab_key_t str){
	uint32_t h=0;     // musí mít 32 bitů
	const unsigned char *p;
	for(p=(const unsigned char*)str; *p!='\0'; p++)
		h = 65599*h + *p;
	return h;
}

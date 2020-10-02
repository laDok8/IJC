// Řešení IJC-DU2, příklad b), 19.4.2020
// Autor: Ladislav Dokoupil, FIT
// Přeloženo: gcc 9.3

#include <stdio.h>
#include <ctype.h>
#include "io.h"

int get_word(char *str, int max, FILE *f){
	static int varn;
	int LIMIT = 127;
	char buffer = 0;
	for(int p=0;p<max;p++)
		str[p] = 0;
	int i = 0;
	do{
		buffer = fgetc(f);
		//EOF
		if(buffer == EOF && i == 0)
				return EOF;
		// whitespaces on start
		if(isspace(buffer) && i == 0)
			continue;
		//whitespace
		if(isspace(buffer)){
			break;
		}
		str[i] = buffer;
		//long??
		if(i == (max-1) || i == (LIMIT-1)){
			if(varn == 0){
				fprintf(stderr,"get_word:dlouhe slovo");
				varn = 1;
			}
			str[i-1]='\0';
			//remove remaining part of word
			do{
				buffer = fgetc(f);
			}while(!(isspace(buffer) || buffer == EOF));
			break;
		}
		i++;
	}while(1);

	return 0;
}

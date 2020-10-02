// tail.c
// Řešení IJC-DU2, příklad a), 19.4.2020
// Autor: Ladislav Dokoupil, FIT
// Přeloženo: gcc 9.3
//obdoba programu tail v bash

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIMIT 1024

//universal read, filename = NULL for stdin
int writeLines(const char *filename, int nLines, int printAll){
	int pom=0;
	FILE *fp;
	if(filename == NULL)
		fp = stdin;
	else{
		fp = fopen(filename,"r");
		if(fp == NULL)
			return 1;
	}
	//fp - file/stdin
	//store all lines as 2d array
	char **str = malloc(sizeof(char*));
	if(str == NULL){
		fprintf(stderr,"malloc error");
		return 1;
	}
	int varn=0;
	for (pom = 0;; pom++) {
		str = realloc(str, (pom + 1) * sizeof(char *));
		if(str == NULL){
			fprintf(stderr,"realloc error");
			return 1;
		}
		str[pom] = malloc(LIMIT * sizeof(char));
		if(str[pom] == NULL){
			fprintf(stderr,"malloc error");
			return 1;
		}
		//EOF check and loading
		if ((fgets(str[pom], LIMIT-1, fp)) == NULL){
			break;
		}
		//line is longer - doesnt contain \n
		if(strchr(str[pom],'\n') == NULL) {
			str[pom][strlen(str[pom])]='\n';
			str[pom][strlen(str[pom])+1]='\0';
			char dumy[LIMIT];
			do{
				//EOF
				if((fgets(dumy, LIMIT, fp) == NULL))
					break;
				if(!varn && dumy != NULL) {
					fprintf(stderr, "dlouhy radek");
					varn = 1;
				}
			}while(strchr(str[pom],'\n') == NULL);
		}
	}
	int printS = pom-nLines;
	if(nLines > pom){
		printS = 0;
	}
	if(printAll == 1){
		printS = nLines-1;
	}
	if(printS<0)
		printS=0;
	//print last nLines
	for(int i = printS;i<pom;i++){
		printf("%s",str[i]);
	}

	//free
	for(int i=0;i<=pom;i++)
		free(str[i]);
	free(str);
	fclose(fp);

	return 0;
}

int main(int argc, char **argv){
	int err=0;
	int nlines=10;
	int printAll=0;
	char *fileName = NULL;
	if(argc == 2){
		fileName = argv[1];
		nlines = 10;
	}
	if(argc > 2) {
		if (!strcmp(argv[1], "-n")) {
			nlines = strtol(argv[2], NULL, 10);
			if(strchr(argv[2],'+')!= NULL)
				printAll=1;
			nlines = abs(nlines);
			if (argc == 4)
				fileName = argv[3];
		}
		else{
			nlines = 10;
			if(argc == 2)
				fileName = argv[1];
		}
	}
	err = writeLines(fileName, nlines,printAll);
	if(err != 0){
		fprintf(stderr,"chyba souboru");
		return 1;
	}
	return 0;
}
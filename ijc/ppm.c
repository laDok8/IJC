// ppm.c
// Řešení IJC-DU1, příklad a), 18.3.2020
// Autor: Ladislav Dokoupil, FIT
// Přeloženo: gcc 9.2.1

#include "ppm.h"
#include "error.h"
#include <stdlib.h>
#include <stdio.h>

struct ppm * ppm_read(const char * filename){
    struct ppm *pp = NULL;
    FILE * fp;
    int  x,y,count,nmemb;
	int  c1;
    fp  = fopen(filename, "r");
    if(fp == NULL)
    	error_exit("ppm.c: soubor nexistuje");
    count = fscanf(fp, "P6 %d %d 255 ",&x,&y);
    if(count != 2 || x > LIMIT || x < 0 || y > LIMIT || y < 0 ){
    	fclose(fp);
    	warning_msg("ppm.c: chyba formatu");
		return NULL;
    }
    nmemb = 3*x*y*sizeof(char);
    pp = malloc(sizeof(struct ppm)+nmemb);
    if(pp == NULL){
    	fclose(fp);
    	error_exit("ppm.c: alloc error");
    }
    pp->xsize = x;
    pp->ysize = y;
    count = fread(pp->data,sizeof(char),nmemb, fp);
	c1 = fgetc(fp);
    fclose(fp);
	if(c1 != EOF || count != nmemb){
		warning_msg("ppm.c: chyba formatu");
	 	ppm_free(pp);
		return NULL;
	}
    return pp;
}
void ppm_free(struct ppm *p){
    free(p);
}

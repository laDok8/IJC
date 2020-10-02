// ppm.h
// Řešení IJC-DU1, příklad a), 18.3.2020
// Autor: Ladislav Dokoupil, FIT
// Přeloženo: gcc 9.2.1

#ifndef PPM_H
#define PPM_H

struct ppm {
    unsigned xsize;
    unsigned ysize;
    char data[];    // RGB bajty, celkem 3*xsize*ysize
};

#define LIMIT 8000

struct ppm * ppm_read(const char * filename);

void ppm_free(struct ppm *p);

#endif /*PPM_H*/

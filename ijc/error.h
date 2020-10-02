// error.h
// Řešení IJC-DU1, příklad a), 18.3.2020
// Autor: Ladislav Dokoupil, FIT
// Přeloženo: gcc 9.2.1
#ifndef ERROR_H
#define ERROR_H



void warning_msg(const char *fmt, ...);

void error_exit(const char *fmt, ...);

#endif /*ERROR_H*/
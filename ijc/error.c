// error.c
// Řešení IJC-DU1, příklad a), 18.3.2020
// Autor: Ladislav Dokoupil, FIT
// Přeloženo: gcc 9.2.1

#include "error.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void warning_msg(const char *fmt, ...){
    va_list list;
    va_start(list,fmt);
    vfprintf(stderr, fmt, list);
    va_end(list);
}
void error_exit(const char *fmt, ...){
    va_list list;
    va_start(list,fmt);
    vfprintf(stderr,fmt,list);
    va_end(list);
    exit(1);
}
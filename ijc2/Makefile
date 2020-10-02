CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -Wextra -O2 -fPIC
PROGRAMS = tail wordcount wordcount-dynamic
MODULS = htab_begin.o htab_bucket_count.o htab_clear.o htab_end.o htab_erease.o htab_find.o htab_hash_fun.o htab_initdest.o htab_iterator_get_key.o htab_iterator_get_value.o htab_iterator_set_value.o htab_lookup_add.o htab_size.o htab_iterator_next.o htab.o

all:$(PROGRAMS)

.PHONY: clean run zip

tail: tail.c
	$(CC) $(CFLAGS) tail.c -o tail

wordcount: wordcount.o libhtab.a io.o
	$(CC) $(CFLAGS) -o $@ -static $^ -L.

wordcount-dynamic: wordcount.o libhtab.so io.o
	$(CC) $(CFLAGS) -o $@ $^ -L.

libhtab.so: $(MODULS)
	$(CC) $(CFLAGS) -shared -o $@ $^
	##$(CC) $(CFLAGS) -shared -o htab-dynamic.so $(MODULS)

libhtab.a:  $(MODULS)
	ar crs $@ $^

wordcountHASHTEST: wordcount.o libhtab.a io.o
	$(CC) $(CFLAGS) -DHASHTEST -o $@  wordcount.c libhtab.a io.o -L.

clean:
	rm -f $(PROGRAMS) *.o *.so *.a htab-dynamic.so htab-static.a wordcountHASHTEST

zip:
	zip xdokou14.zip *.c *.h Makefile

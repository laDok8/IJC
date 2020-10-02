                      Domácí úkol č.1

Příklady: (budou opravovány v prostředí Linux/GCC,
           LC_ALL=cs_CZ.utf8
           překlad: gcc -g -std=c11 -pedantic -Wall -Wextra 
           C11 je potřeba jen pro static_assert(test,"zprava"); )

A) V rozhraní "bitset.h" definujte pro datovou strukturu typu pole bitů:

   Typ:
     typedef <DOPLNIT> bitset_t;
       Typ bitového pole (pro předávání parametru do funkce odkazem).

     typedef unsigned long bitset_index_t;
        Typ indexu do bitového pole.

   Makra:
     bitset_create(jmeno_pole,velikost)
       definuje a _nuluje_ proměnnou jmeno_pole
       (POZOR: opravdu musí _INICIALIZOVAT_ pole bez ohledu na
       to, zda je pole statické nebo automatické/lokální!
       Vyzkoušejte obě varianty, v programu použijte lokální pole.)
       Použijte  static_assert  pro kontrolu velikosti pole.
       Př: static bitset_create(p,100); // p = pole 100 bitů, nulováno
           bitset_create(q,100000L);    // q = pole 100000 bitů, nulováno
           bitset_create(q,-100);       // chyba při překladu

     bitset_alloc(jmeno_pole,velikost)
       definuje proměnnou jmeno_pole tak, aby byla kompatibilní s polem
       vytvořeným pomocí bitset_create, ale pole bude alokováno dynamicky.
       Př: bitset_alloc(q,100000L); // q = pole 100000 bitů, nulováno
       Použijte  assert  pro kontrolu maximální možné velikosti pole.
       Pokud alokace selže, ukončete program s chybovým hlášením:
       "bitset_alloc: Chyba alokace paměti"

     bitset_free(jmeno_pole)
       uvolní paměť dynamicky alokovaného pole

     bitset_size(jmeno_pole)
       vrátí deklarovanou velikost pole v bitech (uloženou v poli)

     bitset_setbit(jmeno_pole,index,výraz)
       nastaví zadaný bit v poli na hodnotu zadanou výrazem
       (nulový výraz == bit 0, nenulový výraz == bit 1)
       Př: bitset_setbit(p,20,1);

     bitset_getbit(jmeno_pole,index)
       získá hodnotu zadaného bitu, vrací hodnotu 0 nebo 1
       Př: if(bitset_getbit(p,i)==1) printf("1");
           if(!bitset_getbit(p,i))   printf("0");

   Kontrolujte meze polí. V případě chyby volejte funkci

     error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu",
               (unsigned long)index, (unsigned long)mez).

   (Použijte například modul error.c/error.h z příkladu b)

   Programy musí fungovat na 32 (gcc -m32) i 64bitové platformě.

   Podmíněným překladem zajistěte, aby se při definovaném symbolu
   USE_INLINE místo těchto maker definovaly inline funkce stejného jména
   všude kde je to možné (bez změn v následujícím testovacím příkladu!).
   Pozor: USE_INLINE nesmí být definováno ve zdrojovém textu --
          překládá se s argumentem -D (gcc -DUSE_INLINE ...).

   Program musí fungovat s inline funkcemi i pro vypnuté optimalizace -O0
   (ověřte si to, vyžaduje modul s externími definicemi inline funkcí).

   Pro vaši implementaci použijte pole typu  unsigned long [].
   V tomto poli na indexu 0 bude velikost bitového pole v bitech.
   Implementace musí efektivně využívat paměť (využít každý
   bit pole až na posledních maximálně CHAR_BIT*sizeof(unsigned long)-1 bitů).


   Jako testovací příklad implementujte funkci, která použije algoritmus známý
   jako Eratostenovo síto (void Eratosthenes(bitset_t pole);) a použijte ji
   pro výpočet posledních 10 prvočísel ze všech prvočísel od 2 do
   N=500000000 (500 milionů). (Doporučuji program nejdříve odladit pro N=100.)
   Funkci Eratosthenes napište do samostatného modulu "eratosthenes.c".

   Každé prvočíslo tiskněte na zvláštní řádek v pořadí
   vzestupném.  Netiskněte  nic  jiného  než  prvočísla (bude se
   automaticky  kontrolovat!).  Pro kontrolu správnosti prvočísel
   můžete použít program "factor" (./primes|factor).

   Naprogramujte (s využitím funkce clock()) měření doby běhu programu v
   sekundách a výsledek vypište na stderr následujícím příkazem:
     fprintf(stderr, "Time=%.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC);
   (Porovnejte s výsledkem programu "time ./primes".)

   Pro lokální pole budete potřebovat zvětšit limit velikosti zásobníku.
   Na Unix-like systémech můžete použít příkaz "ulimit -a" pro zjištění velikosti
   limitu a potom "ulimit -s zadana_velikost_v_KiB" před spuštěním programu.
   (Toto názorně demonstruje nevhodnost používání velkých lokálních polí.)

   Zdrojový text programu se musí jmenovat "primes.c" !
   Napište Makefile tak, aby příkaz "make" vytvořil všechny varianty:
     primes      používá makra
     primes-i    používá inline funkce
   a aby příkaz "make run" všechny varianty vytvořil a spustil.

   (Při nesplnění výše uvedených podmínek: až 0 bodů.)

(7b)

Poznámky:  Eratosthenovo síto (přibližná specifikace):
   1) Nulujeme bitové pole  p  o rozměru N,
      p[0]=1; p[1]=1; // 0 a 1 nejsou prvočísla
      index i nastavit na 2
   2) Vybereme nejmenší index i, takový, že p[i]==0.
      Potom je i prvočíslo
   3) Pro všechny násobky i nastavíme bit p[n*i] na 1
      ('vyškrtneme' násobky - nejsou to prvočísla)
   4) i++; dokud nejsme za sqrt(N), opakujeme bod 2 až 4
      (POZOR: sestavit s matematickou knihovnou parametrem -lm)
   5) Výsledek: v poli p jsou na prvočíselných indexech hodnoty 0

   https://en.wikipedia.org/wiki/Prime_number

   Efektivita výpočtu: cca 3.9s na Intel i5-4690 @ 3.50GHz (gcc -O2)
   Porovnejte efektivitu obou variant (makra vs. inline funkce).
   Zamyslete se, jak by se ověřila efektivita pro (neinline) funkce.



B) Napište modul "error.c" s rozhraním v "error.h", který definuje
   funkci void warning_msg(const char *fmt, ...) a
   funkci void error_exit(const char *fmt, ...). Tyto funkce mají
   stejné parametry jako printf(); tisknou text "CHYBA: " a potom
   chybové hlášení podle formátu fmt. Vše se tiskne do stderr
   (funkcí vfprintf) a potom pouze error_exit ukončí program voláním
   funkce exit(1).  Použijte definice ze stdarg.h.

 * Napište modul "ppm.c" s rozhraním "ppm.h",
   ve kterém definujete typ:

     struct ppm {
        unsigned xsize;
        unsigned ysize;
        char data[];    // RGB bajty, celkem 3*xsize*ysize
     };

   a funkci:

     struct ppm * ppm_read(const char * filename);
        načte obsah PPM souboru do touto funkcí dynamicky
        alokované struktury. Při chybě formátu použije funkci warning_msg
        a vrátí NULL.  Pozor na "memory leaks".

     void ppm_free(struct ppm *p);
        uvolní paměť dynamicky alokovanou v ppm_read

    Můžete doplnit další funkce, ale pro DU1 to není nutné.
    [Zamyslete se nad (ne)vhodností použití warning_msg() a promyslete
    alternativní způsoby hlášení různých chyb.]

    Můžete omezit max. velikost obrazových dat vhodným implementačním
    limitem (např 8000*8000*3).

    Popis formátu PPM najdete na Internetu, implementujte pouze
    binární variantu P6 s barvami 0..255 a bez komentářů:
      "P6" <ws>+
      <xsizetxt> <ws>+ <ysizetxt> <ws>+
      "255" <ws>
      <binární data, 3*xsize*ysize bajtů RGB>
      <EOF>

  * Napište testovací program "steg-decode.c", kde ve funkci main načtete ze
    souboru zadaného jako jediný argument programu obrázek ve formátu PPM
    a v něm najdete uloženou "tajnou" zprávu. Zprávu vytisknete na stdout.

    Zpráva je řetězec znaků (char, včetně '\0') uložený po jednotlivých bitech
    (počínaje LSb) na nejnižších bitech (LSb) vybraných bajtů barevných složek
    v datech obrázku. Dekódování ukončete po dosažení '\0'.
    Pro DU1 budou vybrané bajty určeny prvočísly (počínaje od 23) -- použijte
    Eratostenovo síto podobně jako v příkladu "primes.c" a začněte prvočíslem 23.
    Velikost bitového pole musí odpovídat velikosti obrazových dat.

    Program použije error_exit v případě chyby čtení souboru (chybný formát),
    a v případě, že zpráva není korektně ukončena '\0'. Předpokládejte
    možnost uložení textu zprávy ve formátu UTF-8.

    Použijte program "make" pro překlad/sestavení programu.
    Testovací příkaz:  ./steg-decode du1-obrazek.ppm

    Zájemci si mohou vytvořit i program "steg-encode.c" (nehodnotí se).
    Zamyslete se nad (ne)vhodností použití implementačních limitů.

(8b)

   Zařiďte, aby příkaz "make" bez parametrů vytvořil všechny spustitelné
   soubory pro DU1.  Při změně kteréhokoli souboru musí přeložit jen změněný
   soubor a závislosti. Pokud bude Makefile vypadat jako skript, odečtou se 3b.



                         Domácí úkol č.2

1) (max 5b)
   a) V jazyku C napište program "tail.c", který  ze zadaného
   vstupního souboru vytiskne posledních  10 řádků. Není-li
   zadán vstupní soubor, čte ze stdin. Je-li programu zadán
   parametr -n číslo, bude se tisknout tolik posledních řádků,
   kolik je zadáno parametrem 'číslo' > 0.
   Případná chybová hlášení tiskněte do stderr. Příklady:

     tail soubor
     tail -n +3 soubor
     tail -n 20 <soubor

   [Poznámka: výsledky by měly být +-stejné jako u POSIX příkazu tail]

   Je povolen implementační limit na délku řádku (např. 1023 znaků),
   v případě prvního překročení mezí hlaste chybu na stderr (řádně otestujte)
   a pokračujte se zkrácenými řádky (zbytek řádku přeskočit/ignorovat).


2) (max 10b)
   Přepište následující C++ program do jazyka ISO C

    // wordcount-.cc
    // Použijte: g++ -std=c++11 -O2
    // Příklad použití STL kontejneru unordered_map<>
    // Program počítá četnost slov ve vstupním textu,
    // slovo je cokoli oddělené "bílým znakem"

    #include <string>
    #include <iostream>
    #include <unordered_map>

    int main() {
        using namespace std;
        unordered_map<string,int> m;  // asociativní pole
                     // mapuje klíč/string na hodnotu/int
        string word;
        while (cin >> word) // čtení slova (jako scanf "%s", ale bezpečné)
            m[word]++;      // počítání výskytů slova (zvýší hodnotu pro
                            // zadaný klíč/slovo pokud záznam existuje,
                            // jinak vytvoří nový záznam s hodnotou 0 a
                            // tu operace ++ zvýší na 1)

        for (auto &mi: m)   // pro všechny prvky kontejneru m
            cout << mi.first << "\t" << mi.second << "\n";
            //      klíč/slovo          hodnota/počet
            // prvky kontejneru typu "map" jsou dvojice (klíč,hodnota)
    }

   Výstupy programů musí být pro stejný vstup stejné (kromě pořadí a příliš
   dlouhých slov).

   Výsledný program se musí jmenovat "wordcount.c".

   Implementujte tabulku s rozptýlenými položkami (hash table) - viz dále.
   Veškeré operace s tabulkou budou v samostatné knihovně (vytvořte statickou
   i dynamickou/sdílenou verzi).  V knihovně musí být prakticky každá funkce ve
   zvláštním modulu -- to například umožní případnou výměnu htab_hash_fun() ve vašem
   staticky sestaveném programu. (V dynamicky sestaveném programu je to možné vždy.)
   Vyzkoušejte si to: definujte svoji verzi htab_hash_fun() v programu
   s podmíněným překladem -- použijte #ifdef HASHTEST.

   Knihovna s tabulkou se musí jmenovat
   "libhtab.a" (na Windows je možné i "htab.lib") pro statickou variantu,
   "libhtab.so" (na Windows je možné i "htab.dll") pro sdílenou variantu
   a rozhraní "htab.h".

   Podmínky:
    - Implementace musí být dynamická (malloc/free) a musíte zvládnout
      správu paměti v C (použijte valgrind, nebo jiný podobný nástroj).

    - Vhodná rozptylovací funkce pro řetězce je podle literatury
      (http://www.cse.yorku.ca/~oz/hash.html - varianta sdbm):

        size_t htab_hash_fun(const char *str) {
          uint32_t h=0;     // musí mít 32 bitů
          const unsigned char *p;
          for(p=(const unsigned char*)str; *p!='\0'; p++)
              h = 65599*h + *p;
          return h;
        }

      její výsledek modulo arr_size určuje index do tabulky:
        index = (htab_hash_fun("mystring") % arr_size);
      Zkuste použít i jiné podobné funkce a porovnejte efektivitu.

    - Tabulka je (pro knihovnu privátní) struktura obsahující pole seznamů,
      jeho velikost a počet položek tabulky v následujícím pořadí:

         +----------+
         | size     | // aktuální počet záznamů [key,data,next]
         +----------+
         | arr_size | // velikost následujícího pole ukazatelů
         +----------+
         +---+
         |ptr|-->[key,data,next]-->[key,data,next]-->[key,data,next]--|
         +---+
         |ptr|--|
         +---+
         |ptr|-->[key,data,next]-->[key,data,next]--|
         +---+
         |ptr|--|
         +---+

      Položka .arr_size je velikost následujícího pole ukazatelů (použijte
      C99: "flexible array member"). Paměť pro strukturu se dynamicky alokuje
      tak velká, aby se do ní vešly i všechny položky pole.
      V programu zvolte vhodnou velikost pole a v komentáři zdůvodněte vaše
      rozhodnutí.
      (V obrázku platí velikost .arr_size==4 a počet položek .size==5.)
      Rozhraní knihovny obsahuje jen _neúplnou_deklaraci_ struktury, definice
      je uživateli knihovny skryta (jde o formu zapouzdření - "encapsulation").

    - Napište funkce podle následujícího hlavičkového souboru (API):

==================================================================
// htab.h -- rozhraní knihovny htab (řešení IJC-DU2)
// Licence: žádná (Public domain)

// následující řádky zabrání násobnému vložení:
#ifndef __HTAB_H__
#define __HTAB_H__

#include <string.h>     // size_t
#include <stdbool.h>    // bool

// Tabulka:
struct htab;    // neúplná deklarace struktury - uživatel nevidí obsah
typedef struct htab htab_t;     // typedef podle zadání

// Typy:
typedef const char * htab_key_t;        // typ klíče
typedef int htab_value_t;               // typ hodnoty

// Iterátor do tabulky:
struct htab_item;               // neúplná deklarace struktury

// iterátor:
typedef struct htab_iterator {
    struct htab_item *ptr;      // ukazatel na položku
    const htab_t *t;            // ve které tabulce
    size_t idx;                 // ve kterém seznamu tabulky (TODO: optimalizovat?)
} htab_iterator_t;              // typedef podle zadání

// rozptylovací (hash) funkce (stejná pro všechny tabulky v programu)
// pokud si v programu definujete stejnou funkci, použije se ta vaše
size_t htab_hash_fun(htab_key_t str);

// funkce pro práci s tabulkou:
htab_t *htab_init(size_t n);                    // konstruktor tabulky
size_t htab_size(const htab_t * t);             // počet záznamů v tabulce
size_t htab_bucket_count(const htab_t * t);     // velikost pole

htab_iterator_t htab_find(htab_t * t, htab_key_t key);  // hledání
htab_iterator_t htab_lookup_add(htab_t * t, htab_key_t key);

void htab_erase(htab_t * t, htab_iterator_t it);  // ruší zadaný záznam

htab_iterator_t htab_begin(const htab_t * t);   // iterátor na první záznam
htab_iterator_t htab_end(const htab_t * t);     // iterátor _za_ poslední záznam

htab_iterator_t htab_iterator_next(htab_iterator_t it); // iterátor++

// test: iterátor != end()
inline bool htab_iterator_valid(htab_iterator_t it) { return it.ptr!=NULL; }
// test: iterátor1 == iterátor2
inline bool htab_iterator_equal(htab_iterator_t it1, htab_iterator_t it2) {
  return it1.ptr==it2.ptr && it1.t == it2.t;
}

// čtení a zápis přes iterátor
htab_key_t htab_iterator_get_key(htab_iterator_t it);
htab_value_t htab_iterator_get_value(htab_iterator_t it);
htab_value_t htab_iterator_set_value(htab_iterator_t it, htab_value_t val);

void htab_clear(htab_t * t);    // ruší všechny záznamy
void htab_free(htab_t * t);     // destruktor tabulky

#endif // __HTAB_H__
==================================================================

      Hlavičkový soubor můžete celý převzít (je v "Public domain").

    - Stručný popis základních funkcí:

        t=htab_init(numb)         konstruktor: vytvoření a inicializace tabulky
                                  numb = počet prvků pole (.arr_size)

        size_t s=htab_size(t)           vrátí počet prvků tabulky (.size)

        size_t n=htab_bucket_count(t)   vrátí počet prvků pole (.arr_size)

        iterator=htab_find(t,key)         vyhledávání - viz dále
        iterator=htab_lookup_add(t,key)   vyhledávání+přidání - viz dále

        htab_clear(t)             zrušení všech položek, tabulka zůstane prázdná

        htab_free(t)              destruktor: zrušení tabulky (volá htab_clear())

      kde t,t2    je ukazatel na tabulku (typu htab_t *),
          b       je typu bool,
          ptr     je ukazatel na záznam (položku tabulky),

    - Vhodně zvolte typy parametrů funkcí (včetně použití const).

    - Záznam [key,data,next] je typu
          struct htab_item
      a obsahuje položky:
          key .... ukazatel na dynamicky alokovaný řetězec,
          data ... počet výskytů a
          next ... ukazatel na další záznam
      Tento záznam je definován v privátním hlavičkovém souboru pro všechny
      moduly tabulky a není dostupný při použití knihovny ("Opaque data type").
      Každý iterátor obsahuje ukazatel na tuto strukturu.

    - Funkce
        htab_iterator_t htab_find(htab_t *t, htab_key_t key);
      V tabulce  t  vyhledá záznam odpovídající řetězci  key  a
        - pokud jej nalezne, vrátí iterátor na záznam
        - pokud nenalezne, vrátí iterátor htab_end(t)

    - Funkce
        htab_iterator_t htab_lookup_add(htab_t *t, htab_key_t key);
      V tabulce  t  vyhledá záznam odpovídající řetězci  key  a
        - pokud jej nalezne, vrátí iterátor na záznam
        - pokud nenalezne, automaticky přidá záznam a vrátí iterátor
      Poznámka: Dobře promyslete chování této funkce k parametru key.
      Poznámka: podobně se chová C++ operátor [] pro std::unordered_map

    - Funkce
        void htab_erase(htab_t *t, htab_iterator_t it);
      ruší zadaný záznam v tabulce (dávejte pozor na zneplatnění it touto
      operací - je to potenciální problém i v C++)

    - Když htab_init nebo htab_lookup_add nemohou alokovat paměť,
      vrací NULL nebo nevalidní iterátor htab_end
      (a uživatel musí testovat výsledek těchto operací)

    - Funkce pro iteraci přes prvky tabulky:
        iterator = htab_begin(t)
          vrací iterátor odkazující na první záznam
        iterator = htab_end(t)
          vrací iterátor označující (neexistující) první záznam za koncem
        iterator = htab_iterator_next(iterator)
          posun iterátoru na další záznam v tabulce (nebo na htab_end(t))
          Poznámka: toto dělá i C++ operátor ++ pro iterátory

    - Základní funkce pro testování iterátorů:
        b = htab_iterator_valid(iterator)
          test, zda iterátor označuje platný prvek v tabulce
        b = htab_iterator_equal(iterator1, iterator2)
          porovnání dvou iterátorů na rovnost

    - Funkce pro čtení/zápis přes iterátor:
        cstr = htab_iterator_get_key(iterator);
          vrací klíč, cíl musí existovat
        i = htab_iterator_get_value(iterator);
          vrací hodnotu, cíl musí existovat
        htab_iterator_set_value(iterator, nova_hodnota);
          přepisuje hodnotu, cíl musí existovat


    Napište funkci

        int get_word(char *s, int max, FILE *f);

      která čte jedno slovo ze souboru f do zadaného pole znaků
      a vrátí délku slova (z delších slov načte prvních max-1 znaků,
      a zbytek přeskočí). Funkce vrací EOF, pokud je konec souboru.
      Umístěte ji do zvláštního modulu "io.c" (nepatří do knihovny).
      Poznámka: Slovo je souvislá posloupnost znaků oddělená isspace znaky.

    Omezení: řešení v C bude tisknout jinak uspořádaný výstup
      a je povoleno použít implementační limit na maximální
      délku slova (např. 127 znaků), delší slova se ZKRÁTÍ a program
      při prvním delším slovu vytiskne varování na stderr (max 1 varování).

    Poznámka: Vhodný soubor pro testování je například seznam slov
              v souboru /usr/share/dict/words
              nebo texty z http://www.gutenberg.org/
              případně výsledek příkazu:  "seq 1000000 2000000|shuf"

(10b)

Použijte implicitní lokalizaci (= nevolat setlocale()). Zamyslete se nad tím,
jaké problémy by přineslo použití UTF-8 při zapnuté lokalizaci s tímto
dnes běžně používaným kódováním.

Napište soubor Makefile tak, aby příkaz make vytvořil programy
"tail", "wordcount", "wordcount-dynamic" a knihovny "libhtab.a",
"libhtab.so" (nebo "htab.dll" atd.).

Program "wordcount" musí být staticky sestaven s knihovnou "libhtab.a".

Program "wordcount-dynamic" musí být sestaven s knihovnou "libhtab.so".
Tento program otestujte se stejnými vstupy jako u staticky sestavené verze.

Porovnejte efektivitu obou (C i C++) implementací (viz např. příkaz time)
a zamyslete se nad výsledky (pozor na vliv vyrovnávacích paměťí atd.)
Také si zkuste překlad s optimalizací i bez ní (-O2, -O0) a porovnejte
efektivitu pro vhodný vstup.

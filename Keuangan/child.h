#ifndef CHILD_H_INCLUDED
#define CHILD_H_INCLUDED
#include <iomanip>
#include <iostream>
using namespace std;

#define first(L) L.first
#define last(L) L.last
#define next(P) P->next
#define prev(P) P->prev
#define info(P) P->info

struct infotypec {
    int uang;
    string judul;
};

typedef struct elmc *addressc;

struct elmc {
    infotypec info;
    addressc next;
    addressc prev;
};

struct listc {
    addressc first;
    addressc last;
};


void createlist(listc &L);
addressc allocatec(infotypec X);
void insertlast(listc &L, addressc P);
void deletefirst(listc &L, addressc &C);
void deletelast(listc &L, addressc &C);
void deleteafter(listc &L, addressc prec, addressc &C);
void deletec(listc &L, addressc &C);
void printinfo(listc L);
addressc searchc(listc L, infotypec X);
bool validationc(listc L, infotypec X);

#endif // CHILD_H_INCLUDED

#ifndef PARENT_H_INCLUDED
#define PARENT_H_INCLUDED
#include <iomanip>
#include <iostream>
using namespace std;

#define first(L) L.first
#define next(P) P->next
#define info(P) P->info

struct infotypep {
    string namaperiode;
    string tglmulai;
    string tglakhir;
};

typedef struct elmp *addressp;

struct elmp {
    infotypep info;
    addressp next;
};

struct listp {
    addressp first;
};


void createlist(listp &L);
addressp allocatep(infotypep X);
void insertfirst(listp &L, addressp P);
void insertlast(listp &L, addressp P);
void deletefirst(listp &L, addressp &P);
void deletelast(listp &L, addressp &P);
void deleteafter(listp &L, addressp prec, addressp &P);
void deletep(listp &L, addressp &P);
void printinfo(listp L);
addressp searchp(listp L, infotypep X);
bool validationp(listp L, infotypep X);

#endif // PARENT_H_INCLUDED

#ifndef RELASI_H_INCLUDED
#define RELASI_H_INCLUDED

#include "parent.h"
#include "child.h"
#include <iostream>
#include <iomanip>
using namespace std;

#define first(L) L.first
#define last(L) L.last
#define next(P) P->next
#define prev(P) P->prev
#define parent(P) P->parent
#define child(P) P->child

typedef struct elmr *addressr;

struct elmr {
    addressp parent;
    addressc child;
    addressr next;
    addressr prev;
};

struct listr {
    addressr first;
    addressr last;
};


void createlist(listr &L);
addressr allocater(addressp P, addressc C);
void insertlast(listr &L, addressr R);
void deletefirst(listr &L, addressr &R);
void deletelast(listr &L, addressr &R);
void deleteafter(listr &L, addressr prec, addressr &R);
addressr searchr(listr L, addressp P, addressc C);
addressr searchr(listr L, infotypep px, infotypec cx);
void connect(listr &LR, listp LP, listc LC, infotypep px, infotypec cx);
void printrelasi(listr LR, listp LP);
void deletechildfromparent(listr &LR, listc &LC, addressp P, addressc C);
void deleteallrelations(listr &LR, addressp P);
void findchildinparent(listr LR, addressp P);
void findparentinchild(listr LR, addressc C);
int countchildfromparent(listr &L, addressp P);
void findLargestExpenseInPeriod(listr LR, listp LP, string periode);
#endif // RELASI_H_INCLUDED

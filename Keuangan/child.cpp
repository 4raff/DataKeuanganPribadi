#include "child.h"
#include <iomanip>

void createlist(listc &L) {
    first(L) = NULL;
    last(L) = NULL;
}
bool validationc(listc L, infotypec X){
    addressc P = first(L);
    while (P != NULL) {
        if (info(P).judul == X.judul) {
            return true;
        }
        P = next(P);
    }
    return false;
}
addressc allocatec(infotypec X) {
    addressc P = new elmc;
    info(P) = X;
    next(P) = NULL;
    prev(P) = NULL;
    return P;
}

void insertlast(listc &L, addressc P) {
    if (first(L) == NULL) {
        first(L) = P;
        last(L) = P;
    } else {
        prev(P) = last(L);
        next(last(L)) = P;
        last(L) = P;
    }
}

void deletefirst(listc &L, addressc &C) {
    if (first(L) != NULL) {
        C = first(L);
        if (next(C) == NULL) {
            first(L) = NULL;
            last(L) = NULL;
        } else {
            first(L) = next(C);
            prev(first(L)) = NULL;
        }
        next(C) = NULL;
        prev(C) = NULL;
    }
}

void deletelast(listc &L, addressc &C) {
    if (last(L) != NULL) {
        C = last(L);
        if (prev(C) == NULL) {
            first(L) = NULL;
            last(L) = NULL;
        } else {
            last(L) = prev(C);
            next(last(L)) = NULL;
        }
        next(C) = NULL;
        prev(C) = NULL;
    }
}

void deleteafter(listc &L, addressc prec, addressc &C) {
    if (prec != NULL && next(prec) != NULL) {
        C = next(prec);
        next(prec) = next(C);
        if (next(C) != NULL) {
            prev(next(C)) = prec;
        } else {
            last(L) = prec;
        }
        next(C) = NULL;
        prev(C) = NULL;
    }
}

void deletec(listc &L, addressc &C) {
    if (C == first(L)) {
        deletefirst(L, C);
    } else if (C == last(L)) {
        deletelast(L, C);
    } else {
        addressc prevC = prev(C);
        deleteafter(L, prevC, C);
    }
}



void printinfo(listc L) {
    addressc Q = first(L);
    int count = 1; // Untuk menampilkan nomor urut

    if (Q == NULL) {
        cout << "+----------------------------+" << endl;
        cout << "|     Data Keuangan Kosong   |" << endl;
        cout << "+----------------------------+" << endl;
        return;
    }

    while (Q != NULL) {
        cout << "+----------------------------+" << endl;
        cout << "|       Data Keuangan " << setw(3) << right << count++ << endl;
        cout << "+----------------------------+" << endl;
        cout << "| Uang  : " << setw(20) << left << info(Q).uang << endl;
        cout << "| Judul : " << setw(20) << left << info(Q).judul << endl;
        cout << "+----------------------------+" << endl;
        Q = next(Q);
    }
}



addressc searchc(listc L, infotypec X) {
    addressc Q = first(L);
    while (Q != NULL) {
        if (info(Q).judul == X.judul) {
            return Q;
        }
        Q = next(Q);
    }
    return NULL;
}

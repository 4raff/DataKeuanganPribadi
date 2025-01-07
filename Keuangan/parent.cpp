#include "parent.h"
#include <iomanip>
void createlist(listp &L) {
    first(L) = NULL;
}
bool validationp(listp L, infotypep X){
    addressp P = first(L);
    while (P != NULL) {
        if (info(P).namaperiode == X.namaperiode) {
            return true;
        }
        P = next(P);
    }
    return false;
}
addressp allocatep(infotypep X) {
    addressp P = new elmp;
    info(P) = X;
    next(P) = NULL;
    return P;
}

void insertfirst(listp &L, addressp P) {
    if (first(L) == NULL) {
        first(L) = P;
    } else {
        next(P) = first(L);
        first(L) = P;
    }
}

void insertlast(listp &L, addressp P) {
    if (first(L) == NULL) {
        first(L) = P;
    } else {
        addressp Q = first(L);
        while (next(Q) != NULL) {
            Q = next(Q);
        }
        next(Q) = P;
    }
}

void printinfo(listp L) {
    addressp Q = first(L);

    cout << "+------------------------------------------------------------+" << endl;
    cout << "|                      Data Periode Waktu                   " << endl;
    cout << "+--------------------+--------------------+------------------+" << endl;
    cout << "| Nama Periode       | Tanggal Mulai      | Tanggal Selesai  " << endl;
    cout << "+--------------------+--------------------+------------------+" << endl;

    if (Q == NULL) {
        cout << "|                 Tidak ada data periode yang tersedia      " << endl;
        cout << "+------------------------------------------------------------+" << endl;
        return;
    }

    while (Q != NULL) {
        cout << "| " << setw(18) << left << info(Q).namaperiode
             << "| " << setw(18) << left << info(Q).tglmulai
             << "| " << setw(16) << left << info(Q).tglakhir << endl;
        Q = next(Q);
    }

    cout << "+--------------------+--------------------+------------------+" << endl;
}


addressp searchp(listp L, infotypep X) {
    addressp Q = first(L);
    while (Q != NULL) {
        if (info(Q).namaperiode == X.namaperiode) {
            return Q;
        }
        Q = next(Q);
    }
    return NULL;
}

void deletefirst(listp &L, addressp &P) {
    if (first(L) != NULL) {
        P = first(L);
        first(L) = next(P);
        next(P) = NULL;
    }
}

void deletelast(listp &L, addressp &P) {
    if (first(L) != NULL) {
        addressp Q = first(L);
        if (next(Q) == NULL) {
            P = Q;
            first(L) = NULL;
        } else {
            while (next(next(Q)) != NULL) {
                Q = next(Q);
            }
            P = next(Q);
            next(Q) = NULL;
        }
    }
}


void deleteafter(listp &L, addressp prec, addressp &P) {
    if (prec != NULL && next(prec) != NULL) {
        P = next(prec);
        next(prec) = next(P);
        next(P) = NULL;
    }
}

void deletep(listp &L, addressp &P) {
    if (P == first(L)) {
        deletefirst(L, P);
    } else {
        addressp Q = first(L);
        while (next(Q) != P) {
            Q = next(Q);
        }
        deleteafter(L, Q, P);
    }
}

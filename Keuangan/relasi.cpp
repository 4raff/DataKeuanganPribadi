#include "relasi.h"
#include <iomanip>
void createlist(listr &L) {
    first(L) = NULL;
}

addressr allocater(addressp P, addressc C) {
    addressr R = new elmr;
    parent(R) = P;
    child(R) = C;
    next(R) = NULL;
    prev(R) = NULL;
    return R;
}

void insertlast(listr &L, addressr R) {
    if (first(L) == NULL) {
        first(L) = R;
        last(L) = R;
    } else {
        prev(R) = last(L);
        next(last(L)) = R;
        last(L) = R;
    }
}

void deletefirst(listr &L, addressr &R) {
    if (first(L) != NULL) {
        R = first(L);
        if (first(L) == last(L)) {
            first(L) = NULL;
            last(L) = NULL;
        } else {
            first(L) = next(R);
            next(R) = NULL;
            prev(first(L)) = NULL;
        }
    }
}

void deletelast(listr &L, addressr &R) {
    if (first(L) != NULL) {
        R = last(L);
        if (first(L) == last(L)) {
            first(L) = NULL;
            last(L) = NULL;
        } else {
            last(L) = prev(last(L));
            prev(R) = NULL;
            next(last(L)) = NULL;
        }
    }
}


void deleteafter(listr &L, addressr prec, addressr &R) {
    R = next(prec);
    next(prec) = next(R);
    prev(next(R)) = prec;
    prev(R) = NULL;
    next(R) = NULL;
}


addressr searchr(listr L, addressp P, addressc C) {
    addressr R = first(L);
    while (R != NULL) {
        if (parent(R) == P && child(R) == C) {
            return R;
        }
        R = next(R);
    }
    return NULL;
}

addressr searchr(listr L, infotypep px, infotypec cx) {
    addressr R = first(L);
    while (R != NULL) {
        if (info(parent(R)).namaperiode == px.namaperiode && info(child(R)).uang == cx.uang) {
            return R;
        }
        R = next(R);
    }
    return NULL;
}

void connect(listr &LR, listp LP, listc LC, infotypep px, infotypec cx) {
    addressp P = searchp(LP, px);
    addressc C = searchc(LC, cx);
    if (P != NULL && C != NULL) {
        addressr R = allocater(P, C);
        insertlast(LR, R);
        cout << "Relasi berhasil dibuat antara " << px.namaperiode << " dan pengeluaran " << cx.judul << "." << endl;
    } else {
        cout << "Data tidak valid! Periode atau Pengeluaran tidak ditemukan." << endl;
        return;
    }
}

void printrelasi(listr LR, listp LP) {
    addressp P = first(LP);
    cout << "+------------------------------------------------------+" << endl;
    cout << "|            Data Periode dan Keuangan                |" << endl;
    cout << "+------------------------------------------------------+" << endl;

    if (P == NULL) {
        cout << "|                 Tidak ada data                      |" << endl;
        cout << "+------------------------------------------------------+" << endl;
        return;
    }

    while (P != NULL) {
        cout << "+------------------------------------------------------+" << endl;
        cout << "| Periode: " << setw(38) << left
             << (info(P).namaperiode + " (" + info(P).tglmulai + " - " + info(P).tglakhir + ")") << " |" << endl;
        cout << "+------------------------------------------------------+" << endl;

        addressr R = first(LR);
        bool foundChild = false;

        while (R != NULL) {
            if (parent(R) == P) {
                cout << "| Pengeluaran: " << setw(12) << left << info(child(R)).uang
                     << "| Judul: " << setw(25) << left << info(child(R)).judul << endl;
                foundChild = true;
            }
            R = next(R);
        }

        if (!foundChild) {
            cout << "|             Tidak ada Detil Pengeluaran              |" << endl;
        }

        cout << "+------------------------------------------------------+" << endl;
        P = next(P);
    }

    cout << "|                  End of List                        |" << endl;
    cout << "+------------------------------------------------------+" << endl;
}


void deletechildfromparent(listr &LR, listc &LC, addressp P, addressc C) {
    addressr R = first(LR);
    bool found = false;

    while (R != NULL) {
        addressr nextR = next(R);
        if (parent(R) == P && child(R) == C) {
            found = true;
            if (R == first(LR)) {
                deletefirst(LR, R);
            } else if (R == last(LR)) {
                deletelast(LR, R);
            } else {
                addressr prec = prev(R);
                deleteafter(LR, prec, R);
            }
            cout << "Data Keuangan berhasil dihapus dari periode ini." << endl;
        }
        R = nextR;
    }

    if (!found) {
        cout << "Data Keuangan ini tidak ada di periode yang dituju." << endl;
    }
}

void deleteallrelations(listr &LR, addressp P) {
    addressr R = first(LR);
    addressr nextR;
    while (R != NULL) {
        nextR = next(R);

        if (parent(R) == P) {
            if (R == first(LR)) {
                deletefirst(LR, R);
            } else if (R == last(LR)) {
                deletelast(LR, R);
            } else {
                addressr prec = prev(R);
                deleteafter(LR, prec, R);
            }
        }
        R = nextR;
    }
}


void findchildinparent(listr LR, addressp P) {
    addressr R = first(LR);
    cout << "+--------------------------------------------------------+" << endl;
    cout << "|        Data Keuangan pada Periode: " << setw(23) << left << info(P).namaperiode << endl;
    cout << "+----------------------+---------------------------------+" << endl;
    cout << "| Pengeluaran (Uang)   | Judul Pengeluaran              |" << endl;
    cout << "+----------------------+---------------------------------+" << endl;

    bool found = false;

    while (R != NULL) {
        if (parent(R) == P) {
            cout << "| " << setw(20) << left << info(child(R)).uang
                 << "| " << setw(31) << left << info(child(R)).judul << endl;
            found = true;
        }
        R = next(R);
    }

    if (!found) {
        cout << "|                 Tidak ada data pengeluaran             |" << endl;
    }

    cout << "+----------------------+---------------------------------+" << endl;
}
void findparentinchild(listr LR, addressc C) {
    addressr R = first(LR);
    cout << "+--------------------------------------------------------+" << endl;
    cout << "|        Data Keuangan pada Pengeluaran: " << setw(23) << left << info(C).judul << endl;
    cout << "+----------------------+-----------------------------------------+" << endl;
    cout << "| Pengeluaran (Uang)   | Judul Pengeluaran    | Berelasi Dengan  |" << endl;
    cout << "+----------------------+----------------------+------------------+" << endl;

    bool found = false;

    while (R != NULL) {
        if (child(R) == C) {
            cout << "| " << setw(20) << left << info(child(R)).uang
                 << "| " << setw(22) << left << info(child(R)).judul
                 << "| " << setw(18) << left << info(parent(R)).namaperiode << endl;
            found = true;
        }
        R = next(R);
    }

    if (!found) {
        cout << "|                 Tidak ada data pengeluaran             |" << endl;
    }

    cout << "+----------------------+----------------------+------------------+" << endl;
}



int countchildfromparent(listr &L, addressp P) {
    int total = 0;
    int i = 0;
    addressr R = first(L);
    while (R != NULL) {
        if (parent(R) == P) {
            total += info(child(R)).uang;
            i += 1;
        }
        R = next(R);
    }
    cout << "Jumlah Pengeluaran pada Periode " << info(P).namaperiode << ": " << total << endl;
    cout << "Dengan banyaknya keuangan : " << i << " unit" << endl;
}

void findLargestExpenseInPeriod(listr LR, listp LP, string periode) {
    addressp P = first(LP);
    while (P != NULL) {
        if (info(P).namaperiode == periode) {
            addressr R = first(LR);
            int maxExpense = 0;
            string largestTitle;

            while (R != NULL) {
                if (parent(R) == P) {
                    addressc C = child(R);
                    if (info(C).uang > maxExpense) {
                        maxExpense = info(C).uang;
                        largestTitle = info(C).judul;
                    }
                }
                R = next(R);
            }

            // Tampilan hasil dengan format tabel
            if (largestTitle == "") {
                cout << "+------------------------------------------+" << endl;
                cout << "|        Tidak ada pengeluaran             |" << endl;
                cout << "|       pada periode " << setw(19) << left << periode << "|" << endl;
                cout << "+------------------------------------------+" << endl;
            } else {
                cout << "+------------------------------------------+" << endl;
                cout << "| Pengeluaran Terbesar dalam Periode:      |" << endl;
                cout << "| " << setw(38) << left << periode << " |" << endl;
                cout << "+----------------------+-------------------+" << endl;
                cout << "| Judul Pengeluaran    | Jumlah (Uang)     |" << endl;
                cout << "+----------------------+-------------------+" << endl;
                cout << "| " << setw(20) << left << largestTitle
                     << "| " << setw(18) << left << maxExpense << "|" << endl;
                cout << "+----------------------+-------------------+" << endl;
            }

            return;
        }
        P = next(P);
    }

    // Jika periode tidak ditemukan
    cout << "+------------------------------------------+" << endl;
    cout << "|       Periode " << setw(26) << left << periode << "tidak ditemukan! |" << endl;
    cout << "+------------------------------------------+" << endl;
}

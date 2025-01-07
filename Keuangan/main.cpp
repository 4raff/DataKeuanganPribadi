#include <iostream>
#include "parent.h"
#include "child.h"
#include "relasi.h"
#include <iomanip>
using namespace std;

listp tahun;
listc uang;
listr relasi;

void menu() {
    cout << "\n=============================================" << endl;
    cout << "|                    MENU                   |" << endl;
    cout << "=============================================" << endl;
    cout << "| 1.  Masukkan Periode Waktu                |" << endl;
    cout << "| 2.  Masukkan Pengeluaran Keuangan         |" << endl;
    cout << "| 3.  Relasikan Periode Dan Pengeluaran     |" << endl;
    cout << "| 4.  Melihat Data Periode Waktu            |" << endl;
    cout << "| 5.  Melihat Data Pengeluaran              |" << endl;
    cout << "| 6.  Melihat Data Relasi                   |" << endl;
    cout << "| 7.  Cari Periode Waktu                    |" << endl;
    cout << "| 8.  Cari Pengeluaran Keuangan             |" << endl;
    cout << "| 9.  Cari Pengeluaran Berdasarkan Periode  |" << endl;
    cout << "| 10. Cari Periode Berdasarkan Pengeluaran  |" << endl;
    cout << "| 11. Hitung Jumlah Data Keuangan           |" << endl;
    cout << "|     Berdasarkan Periode Tertentu          |" << endl;
    cout << "| 12. Menghapus Periode beserta Relasinya   |" << endl;
    cout << "| 13. Menghapus Data Keuangan Pada Periode  |" << endl;
    cout << "|     Tertentu                              |" << endl;
    cout << "| 14. Melihat Kategori Pengeluaran Terbesar |" << endl;
    cout << "|     Pada Periode Tertentu                 |" << endl;
    cout << "| 0.  Keluar                                |" << endl;
    cout << "=============================================" << endl;
    cout << "Pilih menu: ";
}

int main() {
    createlist(tahun);
    createlist(uang);
    createlist(relasi);

    int choice = -1;
    while (choice != 0) {
        menu();
        cin >> choice;

      if (choice == 1) {
        infotypep Xp;
        int n;
        cout << "Masukkan jumlah data yang ingin ditambah: ";
        cin >> n;
        for (int i = 0; i < n; i++) {
            int posisi;
            cout << "Masukkan Nama Periode ke-" << i + 1 << ": ";
            cin >> Xp.namaperiode;
            if (validationp(tahun, Xp)) {
                cout << "Nama periode sudah ada. Silakan masukkan nama lain." << endl;
                i--;
            } else {
                cout << "Masukan Tanggal Awal: ";
                cin >> Xp.tglmulai;
                cout << "Masukkan Tanggal Akhir: ";
                cin >> Xp.tglakhir;
                cout << "Insert di (1=Depan, 2=Belakang): ";
                cin >> posisi;
                addressp P = allocatep(Xp);
                if (posisi == 1) {
                    insertfirst(tahun, P);
                } else {
                    insertlast(tahun, P);
                }
            }
        }
        cout << "Periode berhasil ditambahkan!" << endl;

    } else if (choice == 2) {
        infotypec Xc;
        int n;
        cout << "Masukkan jumlah data yang ingin ditambah: ";
        cin >> n;
        for (int i = 0; i < n; i++) {
            cout << "Masukkan Nama Pengeluaran ke-" << i + 1 << ": ";
            cin >> Xc.judul;
            if (validationc(uang, Xc)) {
                cout << "Nama pengeluaran sudah ada. Silakan masukkan nama lain." << endl;
                i--;
            } else {
                cout << "Masukkan Detil Pengeluaran: ";
                cin >> Xc.uang;

                addressc C = allocatec(Xc);
                insertlast(uang, C);
            }
        }
        cout << "Pengeluaran berhasil ditambahkan!" << endl;
    } else if (choice == 3) {
            infotypep Xp;
            infotypec Xc;
            int n;
            cout << "Masukkan jumlah data yang ingin direlasikan: ";
            cin >> n;
            for (int i = 0; i < n; i++) {
                cout << "Masukkan Nama Periode: ";
                cin >> Xp.namaperiode;
                cout << "Masukkan Nama Pengeluaran: ";
                cin >> Xc.judul;
                connect(relasi, tahun, uang, Xp, Xc);
            }

        } else if (choice == 4) {
            printinfo(tahun);

        } else if (choice == 5) {
            cout << "Data data keuangan" << endl;
            printinfo(uang);

        } else if (choice == 6) {
            cout << "Data Relasi:" << endl;
            printrelasi(relasi, tahun);

        } else if (choice == 7) {
            infotypep Xp;
            cout << "Masukkan Nama Periode yang Dicari: ";
            cin >> Xp.namaperiode;

            addressp P = searchp(tahun, Xp);
            if (P != NULL) {
                cout << "Periode ditemukan" << endl;
                cout << "Nama Periode || " << info(P).namaperiode << " || Tanggal Mulai || " << info(P).tglmulai << " || Tanggal Selesai || " << info(P).tglakhir << endl;
            } else {
                cout << "Periode tidak ditemukan!" << endl;
            }

        } else if (choice == 8) {
            infotypec Xc;
            cout << "Masukkan Detil Pengeluaran yang Dicari: ";
            cin >> Xc.judul;

            addressc C = searchc(uang, Xc);
            if (C != NULL) {
                cout << "Data ditemukan " << endl;
                cout << "Pengeluaran: " << info(C).uang << "| Judul: " << info(C).judul << endl;
            } else {
                cout << "Data tidak ditemukan!" << endl;
            }

        } else if (choice == 9) {
            infotypep Xp;
            infotypec Xc;
            cout << "Masukkan Nama Periode: ";
            cin >> Xp.namaperiode;
            cout << "Masukkan Nama Pengeluaran: ";
            cin >> Xc.judul;
            addressc C = searchc(uang, Xc);
            addressp P = searchp(tahun, Xp);
            if (P != NULL && C != NULL) {    
                findchildinparent(relasi, P, C);
            } else {
                cout << "Periode/Pengeluaran tidak ditemukan!" << endl;
            }

        } else if (choice == 10) {
            infotypec Xc;
            cout << "Masukkan Judul Pengeluaran: ";
            cin >> Xc.judul;
            addressc C = searchc(uang, Xc);
            if (C != NULL) {   
                findparentinchild(relasi, C);
            } else {
                cout << "Pengeluaran tidak ditemukan!" << endl;
            }

        } else if (choice == 11) {
            infotypep Xp;
            cout << "Masukkan Nama Periode: ";
            cin >> Xp.namaperiode;

            addressp P = searchp(tahun, Xp);
            if (P != NULL) {
                countchildfromparent(relasi, P);
            } else {
                cout << "Periode tidak ditemukan!" << endl;
            }

        } else if (choice == 12) {
            infotypep Xp;
            cout << "Masukkan Nama Periode yang ingin dihapus: ";
            cin >> Xp.namaperiode;

            addressp P = searchp(tahun, Xp);
            if (P != NULL) {
                deleteallrelations(relasi, P);
                deletep(tahun, P);
                cout << "Periode dan relasinya berhasil dihapus!" << endl;
            } else {
                cout << "Periode tidak ditemukan!" << endl;
            }

        } else if (choice == 13) {
            infotypep Xp;
            infotypec Xc;
            cout << "Masukkan Nama Periode: ";
            cin >> Xp.namaperiode;
            cout << "Masukkan Nama Pengeluaran yang ingin dihapus: ";
            cin >> Xc.judul;

            addressp P = searchp(tahun, Xp);
            addressc C = searchc(uang, Xc);
            if (P != NULL && C != NULL) {
                deletechildfromparent(relasi, uang, P, C);
                deletec(uang, C);
            } else {
                cout << "Periode atau Data Keuangan tidak ditemukan!" << endl;
            }

        } else if (choice == 14) {
            string periode;
            cout << "Masukkan nama periode untuk mencari pengeluaran terbesar: ";
            cin >> periode;
            findLargestExpenseInPeriod(relasi, tahun, periode);

        } else if (choice == 0) {
            cout << "Keluar dari program. Terima kasih!" << endl;

        } else {
            cout << "Pilihan tidak valid! Silakan coba lagi." << endl;
        }
    }

    return 0;
}

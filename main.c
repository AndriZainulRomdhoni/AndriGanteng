#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define JUMLAH_PERALATAN 5
#define MAX_TRANSAKSI 10
#define MAX_NAMA 100

// Data peralatan
char peralatan[JUMLAH_PERALATAN][50] = {
    "Tenda Kapasitas 4 Orang",
    "Sleeping Bag",
    "Kompor Portable",
    "Matras Camping",
    "Lampu Camping"
};

int harga[JUMLAH_PERALATAN] = {
    50000, 15000, 20000, 10000, 12000
};

// Array untuk menyimpan riwayat transaksi
char namaPenyewa[MAX_TRANSAKSI][MAX_NAMA];
int nomorPeralatan[MAX_TRANSAKSI];
int jumlahUnit[MAX_TRANSAKSI];
int lamaSewa[MAX_TRANSAKSI];
int totalBayar[MAX_TRANSAKSI];

int jumlahTransaksi = 0;

// Membaca angka dengan validasi
int inputAngka(const char *pesan) {
    char buffer[100];
    char *akhir;
    long angka;

    while (1) {
        printf("%s", pesan);

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            return 0;
        }

        angka = strtol(buffer, &akhir, 10);

        while (isspace((unsigned char)*akhir)) {
            akhir++;
        }

        if (akhir != buffer && *akhir == '\0'
            && angka >= 1 && angka <= 1000000) {
            return (int)angka;
        }

        printf("Input tidak valid! Masukkan angka yang benar.\n");
    }
}

// Membaca nama penyewa
void inputNama(char nama[]) {
    while (1) {
        printf("Nama penyewa: ");

        if (fgets(nama, MAX_NAMA, stdin) == NULL) {
            nama[0] = '\0';
            return;
        }

        nama[strcspn(nama, "\n")] = '\0';

        if (strlen(nama) > 0) {
            return;
        }

        printf("Nama tidak boleh kosong!\n");
    }
}

// Menampilkan daftar peralatan
void tampilkanPeralatan() {
    int i;

    printf("\n========================================\n");
    printf("          DAFTAR PERALATAN\n");
    printf("========================================\n");
    printf("%-4s %-27s %s\n", "No.", "Nama Peralatan", "Harga/Hari");
    printf("----------------------------------------\n");

    for (i = 0; i < JUMLAH_PERALATAN; i++) {
        printf("%-4d %-27s Rp%d\n",
               i + 1, peralatan[i], harga[i]);
    }

    printf("========================================\n");
}

// Menampilkan struk penyewaan
void tampilkanStruk(int index, int subtotal, int diskon, int persen) {
    printf("\n========================================\n");
    printf("          ADVENTURE CAMP\n");
    printf("           STRUK PENYEWAAN\n");
    printf("========================================\n");
    printf("Nama Penyewa   : %s\n", namaPenyewa[index]);
    printf("Peralatan      : %s\n",
           peralatan[nomorPeralatan[index]]);
    printf("Harga per Hari : Rp%d\n",
           harga[nomorPeralatan[index]]);
    printf("Jumlah Unit    : %d\n", jumlahUnit[index]);
    printf("Lama Sewa      : %d hari\n", lamaSewa[index]);
    printf("----------------------------------------\n");
    printf("Subtotal       : Rp%d\n", subtotal);
    printf("Diskon (%d%%)   : Rp%d\n", persen, diskon);
    printf("----------------------------------------\n");
    printf("TOTAL BAYAR    : Rp%d\n", totalBayar[index]);
    printf("========================================\n");
    printf("Terima kasih telah menggunakan\n");
    printf("layanan Adventure Camp!\n");
}

// Proses penyewaan
// Mengembalikan 1 jika transaksi berhasil, 0 jika tidak
int sewaPeralatan() {
    int pilihan, unit, hari;
    int subtotal, persen, diskon;
    char nama[MAX_NAMA];

    if (jumlahTransaksi >= MAX_TRANSAKSI) {
        printf("\nKapasitas transaksi sudah penuh!\n");
        printf("Maksimal %d transaksi.\n", MAX_TRANSAKSI);
        return 0;
    }

    inputNama(nama);

    tampilkanPeralatan();

    while (1) {
        pilihan = inputAngka("Pilih nomor peralatan: ");

        if (pilihan >= 1 && pilihan <= JUMLAH_PERALATAN) {
            break;
        }

        printf("Nomor peralatan tidak tersedia!\n");
    }

    unit = inputAngka("Jumlah unit yang disewa: ");
    hari = inputAngka("Lama penyewaan (hari): ");

    // Menghitung subtotal
    subtotal = harga[pilihan - 1] * unit * hari;

    // Menentukan persentase diskon
    if (hari >= 5) {
        persen = 15;
    } else if (hari >= 3) {
        persen = 10;
    } else {
        persen = 0;
    }

    diskon = subtotal * persen / 100;

    // Menyimpan transaksi ke dalam array
    strcpy(namaPenyewa[jumlahTransaksi], nama);
    nomorPeralatan[jumlahTransaksi] = pilihan - 1;
    jumlahUnit[jumlahTransaksi] = unit;
    lamaSewa[jumlahTransaksi] = hari;
    totalBayar[jumlahTransaksi] = subtotal - diskon;

    tampilkanStruk(jumlahTransaksi, subtotal, diskon, persen);

    jumlahTransaksi++;

    return 1;
}

// Menampilkan riwayat transaksi
void tampilkanRiwayat() {
    int i;
    int totalPendapatan = 0;

    printf("\n========================================\n");
    printf("          RIWAYAT TRANSAKSI\n");
    printf("========================================\n");

    if (jumlahTransaksi == 0) {
        printf("Belum ada transaksi penyewaan.\n");
        printf("========================================\n");
        return;
    }

    printf("%-4s %-18s %-25s %s\n",
           "No.", "Nama", "Peralatan", "Total");
    printf("---------------------------------------------------------------\n");

    for (i = 0; i < jumlahTransaksi; i++) {
        printf("%-4d %-18.18s %-25s Rp%d\n",
               i + 1,
               namaPenyewa[i],
               peralatan[nomorPeralatan[i]],
               totalBayar[i]);

        totalPendapatan += totalBayar[i];
    }

    printf("---------------------------------------------------------------\n");
    printf("Jumlah Transaksi : %d\n", jumlahTransaksi);
    printf("Total Pendapatan : Rp%d\n", totalPendapatan);
    printf("========================================\n");
}

// Menu utama
int main() {
    int menu;
    char kembali;

    do {
        printf("\n========================================\n");
        printf("           ADVENTURE CAMP\n");
        printf("      SISTEM PENYEWAAN PERALATAN\n");
        printf("========================================\n");
        printf("1. Lihat Daftar Peralatan\n");
        printf("2. Sewa Peralatan\n");
        printf("3. Lihat Riwayat Transaksi\n");
        printf("4. Keluar\n");
        printf("========================================\n");

        menu = inputAngka("Pilih menu [1-4]: ");

        switch (menu) {
            case 1:
                tampilkanPeralatan();
                break;

            case 2:
                if (sewaPeralatan()) {
                    while (1) {
                        printf("\nKembali ke menu utama? (Y/T): ");

                        if (scanf(" %c", &kembali) != 1) {
                            kembali = 'T';
                        }

                        // Membersihkan sisa input
                        int ch;
                        while ((ch = getchar()) != '\n' && ch != EOF) {
                        }

                        kembali = (char)toupper((unsigned char)kembali);

                        if (kembali == 'Y' || kembali == 'T') {
                            break;
                        }

                        printf("Masukkan Y untuk kembali atau T untuk keluar.\n");
                    }

                    if (kembali == 'T') {
                        printf("\nTerima kasih telah menggunakan "
                               "Adventure Camp!\n");
                        printf("Program selesai.\n");
                        return 0;
                    }
                }
                break;

            case 3:
                tampilkanRiwayat();
                break;

            case 4:
                printf("\nTerima kasih telah menggunakan "
                       "Adventure Camp!\n");
                printf("Program selesai.\n");
                return 0;

            default:
                printf("Pilihan menu tidak tersedia!\n");
        }

    } while (1);

    return 0;
}

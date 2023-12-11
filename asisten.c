#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cobaLagi(int *lanjut)
{
    printf("Coba Lagi? : ");
    scanf("%d", &lanjut);
}
// Struktur untuk menyimpan informasi kontak
struct Kontak
{
    char nama[50];
    int umur;
};

int main()
{
    FILE *fileDaftarKontak;
    struct Kontak kontak;
    char namaCari[50];
    int menuTerpilih;

    printf("\n=================SELAMAT DATANG DI DASHBOARD KONTAK KARYAWAN=================");
    printf("\n1.Tambah Kontak Karyawan");
    printf("\n2.Cari Kontak Karyawan");
    printf("\nPilih Menu : ");
    scanf("%d", &menuTerpilih);

    switch (menuTerpilih)
    {

    case 1:
        fileDaftarKontak = fopen("userdata.dat", "ab");

        if (fileDaftarKontak == NULL)
        {
            perror("Gagal membuka file");
            exit(EXIT_FAILURE);
        }

        printf("\nMasukan nama : ");
        scanf("%s", &kontak.nama);
        printf("Masukan umur : ");
        scanf("%d", &kontak.umur);

        fwrite(&kontak, sizeof(struct Kontak), 1, fileDaftarKontak);

        break;
    case 2:
        fileDaftarKontak = fopen("userdata.dat", "rb");

        printf("Masukkan nama yang ingin dicari: ");
        scanf("%s", namaCari);

        // Membaca dan menampilkan kontak berdasarkan nama
        while (fread(&kontak, sizeof(struct Kontak), 1, fileDaftarKontak) == 1)
        {
            if (strcmp(kontak.nama, namaCari) == 0)
            {
                // Menampilkan informasi kontak yang sesuai
                printf("Nama: %s\n", kontak.nama);
                printf("Umur: %d\n", kontak.umur);

                break;
            }
        }
        break;

    default:
        printf("Menu Tidak Tersedia!");
        break;
    }

    fclose(fileDaftarKontak);

    return 0;
}

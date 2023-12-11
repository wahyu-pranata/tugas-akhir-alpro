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
    FILE *fileDaftarKontak, *fileTempKontak;
    struct Kontak kontak;
    char namaCari[50];
    int menuTerpilih;

    printf("\n=================SELAMAT DATANG DI DASHBOARD KONTAK KARYAWAN=================");
    printf("\n1.Tambah Kontak Karyawan");
    printf("\n2.Cari Kontak Karyawan");
    printf("\n3.Hapus Kontak Karyawan");
    printf("\n4.Hapus Semua Kontak");
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

    case 3:
        printf("\nMasukan nama kontak: ");
        scanf("%s", &namaCari);

        fileDaftarKontak = fopen("userdata.dat", "rb");
        fileTempKontak = fopen("temp.dat", "wb");

        while (fread(&kontak, sizeof(struct Kontak), 1, fileDaftarKontak) == 1)
        {
            if (strcmp(kontak.nama, namaCari) != 0)
            {
                fwrite(&kontak, sizeof(struct Kontak), 1, fileTempKontak);
            }
        }
        fclose(fileDaftarKontak);
        fclose(fileTempKontak);

        remove("userdata.dat");

        // Mengganti nama file sementara menjadi nama file asli
        rename("temp.dat", "userdata.dat");

        printf("Kontak dengan nama telah dihapus.\n");
        break;

    case 4:
        remove("userdata.dat");
        fileDaftarKontak = fopen("userdata.dat", "w");
        break;

    default:
        printf("Menu Tidak Tersedia!");
        break;
    }

    fclose(fileDaftarKontak);

    return 0;
}

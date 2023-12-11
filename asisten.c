#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

FILE *fileDaftarKontak, *fileTempKontak;

struct Kontak
{
    char nama[50];
    int umur;
} kontak;

// tambah kontak
void tambahKontak()
{
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
    fclose(fileDaftarKontak);
}

void cariKontak(char namaCari[])
{
    fileDaftarKontak = fopen("userdata.dat", "rb");

    while (fread(&kontak, sizeof(struct Kontak), 1, fileDaftarKontak) == 1)
    {
        if (strcmp(kontak.nama, namaCari) == 0)
        {
            printf("Nama: %s\n", kontak.nama);
            printf("Umur: %d\n", kontak.umur);

            break;
        }
    }
    fclose(fileDaftarKontak);
}

void hapusKontak(char namaCari[])
{
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
    remove("userdata.dat");
    fclose(fileTempKontak);
    rename("temp.dat", "userdata.dat");

    // Mengganti nama file sementara menjadi nama file asli

    printf("Kontak telah dihapus.\n");
}
int cobaLagi(char text[])
{
    int cobaLagi;
    printf("%s", text);
    scanf("%d", &cobaLagi);
    return cobaLagi;
}

int main()
{
    int hasil;
    char namaCari[50];
    int menuTerpilih;
    do
    {
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
            do
            {
                tambahKontak();

                hasil = cobaLagi("Tambah Kontak Lain? (1)Ya || (0)Tidak : ");
            } while (hasil == 1);
            break;
        case 2:
            do
            {
                printf("Masukkan nama yang ingin dicari : ");
                scanf("%s", &namaCari);
                cariKontak(namaCari);

                hasil = cobaLagi("Cari Kontak Lain? (1)Ya || (0)Tidak : ");
            } while (hasil == 1);
            break;

        case 3:
            do
            {
                printf("\nMasukan nama kontak: ");
                scanf("%s", &namaCari);

                hapusKontak(namaCari);
                hasil = cobaLagi("Hapus kontak lain? (1)Ya || (0)Tidak  : ");
            } while (hasil == 1);
            break;

        case 4:
            remove("userdata.dat");
            fileDaftarKontak = fopen("userdata.dat", "w");
            break;

        default:
            printf("Menu Tidak Tersedia!");
            break;
        }
        hasil = cobaLagi("Coba Lagi? (1)Ya || (0)Tidak : ");
    } while (hasil == 1);

    return 0;
}

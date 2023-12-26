#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

FILE *fileDaftarKontak, *fileTempKontak;

struct KontakStruct
{
    char nama[50];
    char noTelepon[14];
    char email[99];
    int umur;
} kontak;

void cetakGaris()
{
    printf("======================================================================================================================================================\n");
}

void ulang(void (*func)())
{
    char pilihan[99];

    do
    {
        system("clear");
        func();
        cetakGaris();
        printf("Lagi? \n");
        printf("1 - Iya\n");
        printf("[Any key] - Tidak\n");
        scanf("%s", pilihan);
    } while (strcmp(pilihan, "1") == 0);
}

void keluar()
{
    printf("Kembali?\n");
    printf("1 - Iya\n");

    char choice[99] = "0";
    while (strcmp(choice, "1") != 0)
    {
        scanf("%s", choice);
        if (strcmp(choice, "1") != 0)
        {
            printf("Input salah!\n");
        }
    }
}

void tampilKontak()
{
    FILE *fPointer = fopen("./contacts.dat", "r");

    cetakGaris();

    printf("\n%20s%20s%40s%20s\n", "Nama", "No. Telepon", "Email", "Umur");
    while (fread(&kontak, sizeof(struct KontakStruct), 1, fPointer))
    {
        printf("%20s%20s%40s%20d\n", kontak.nama, kontak.noTelepon, kontak.email, kontak.umur);
    }

    fclose(fPointer);
}

void menuTampilKontak()
{
    system("clear");
    tampilKontak();
    keluar();
}

void tambahKontak()
{
    system("clear");
    fileDaftarKontak = fopen("contacts.dat", "ab");

    cetakGaris();
    printf("Tambah Kontak\n\n");

    if (fileDaftarKontak == NULL)
    {
        perror("Gagal membuka file\n");
        exit(EXIT_FAILURE);
    }
    tampilKontak();

    printf("\n");
    printf("Masukan nama: ");
    scanf("%s", kontak.nama);
    printf("Masukan no. telepon: ");
    scanf("%s", kontak.noTelepon);
    printf("Masukan email: ");
    scanf("%s", kontak.email);
    printf("Masukan umur: ");
    scanf("%d", &kontak.umur);

    int sukses = fwrite(&kontak, sizeof(struct KontakStruct), 1, fileDaftarKontak);
    if (sukses < 1)
    {
        printf("Gagal menginput kontak!\n");
    }
    else
    {
        printf("Kontak berhasil ditambah!\n");
    }
    fclose(fileDaftarKontak);
}

void cariKontak()
{
    system("clear");

    char namaCari[99];

    fileDaftarKontak = fopen("contacts.dat", "rb");

    cetakGaris();
    printf("Cari Kontak\n\n");

    tampilKontak();

    printf("\nMasukan nama kontak: ");
    scanf("%s", namaCari);

    while (fread(&kontak, sizeof(struct KontakStruct), 1, fileDaftarKontak) == 1)
    {
        if (strcmp(kontak.nama, namaCari) == 0)
        {
            printf("Nama: %s\n", kontak.nama);
            printf("No. Telepon: %s\n", kontak.noTelepon);
            printf("Email: %s\n", kontak.email);
            printf("Umur: %d\n", kontak.umur);
            break;
        }
        else
        {
            printf("Kontak tidak ditemukan!\n");
        }
    }
    fclose(fileDaftarKontak);
}

void editKontak()
{
    system("clear");

    char namaCari[99];
    int jumlah = 0;

    fileDaftarKontak = fopen("contacts.dat", "rb");
    fileTempKontak = fopen("temp.dat", "wb");

    cetakGaris();
    printf("Edit Kontak\n\n");

    tampilKontak();

    printf("\nMasukan nama kontak: ");
    scanf("%s", namaCari);

    while (fread(&kontak, sizeof(struct KontakStruct), 1, fileDaftarKontak) == 1)
    {
        if (strcmp(kontak.nama, namaCari) == 0)
        {
            printf("Kontak ditemukan. Silakan masukkan data yang baru:\n");
            jumlah = jumlah + 1;

            printf("Masukan nama: ");
            scanf("%s", kontak.nama);
            printf("Masukan no. telepon: ");
            scanf("%s", kontak.noTelepon);
            printf("Masukan email: ");
            scanf("%s", kontak.email);
            printf("Masukan umur: ");
            scanf("%d", &kontak.umur);
            int sukses = fwrite(&kontak, sizeof(struct KontakStruct), 1, fileTempKontak);

            if (sukses < 1)
            {
                printf("Gagal mengedit kontak!\n");
            }
            else
            {
                printf("Kontak berhasil diedit!\n");
            }
        }
        else
        {
            fwrite(&kontak, sizeof(struct KontakStruct), 1, fileTempKontak);
        }
    }

    if (jumlah == 0)
    {
        printf("Kontak tidak ditemukan\n");
    }

    fclose(fileDaftarKontak);
    remove("contacts.dat");
    fclose(fileTempKontak);
    rename("temp.dat", "contacts.dat");
}

void hapusKontak()
{
    system("clear");

    char namaCari[99];
    int jumlah = 0;

    fileDaftarKontak = fopen("contacts.dat", "rb");
    fileTempKontak = fopen("temp.dat", "wb");

    cetakGaris();
    printf("Hapus Kontak\n\n");

    tampilKontak();

    printf("\nMasukan nama kontak: ");
    scanf("%s", namaCari);

    while (fread(&kontak, sizeof(struct KontakStruct), 1, fileDaftarKontak) == 1)
    {
        if (strcmp(kontak.nama, namaCari) != 0)
        {
            fwrite(&kontak, sizeof(struct KontakStruct), 1, fileTempKontak);
        }
        else
        {
            jumlah = jumlah + 1;
        }
    }

    fclose(fileDaftarKontak);
    remove("contacts.dat");
    fclose(fileTempKontak);
    rename("temp.dat", "contacts.dat");

    if (jumlah == 0)
    {
        printf("Tidak ada data yang terhapus!\n");
    }
    else
    {
        printf("Semua kontak dengan nama %s sudah dihapus!\n", namaCari);
    }
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
    char pilihan;
    do
    {
        system("clear");

        printf("Selamat datang\n");
        printf("Masukkan pilihan: \n");
        printf("1 - Lihat semua kontak\n");
        printf("2 - Tambah kontak\n");
        printf("3 - Cari kontak\n");
        printf("4 - Edit kontak\n");
        printf("5 - Hapus kontak\n");
        printf("6 - Keluar aplikasi\n");

        printf("Masukkan pilihan anda: ");

        scanf("%s", &pilihan);

        switch (pilihan)
        {
        case '1':
            menuTampilKontak();
            break;
        case '2':
            ulang(tambahKontak);
            break;
        case '3':
            ulang(cariKontak);
            break;

        case '4':
            ulang(editKontak);
            break;
        case '5':
            ulang(hapusKontak);
            break;
        case '6':
            printf("Terima kasih. Sampai jumpa :)\n");
            exit(1);
            break;
        default:
            printf("Menu Tidak Tersedia!");
            break;
        }
    } while (true);

    return 0;
}

# SoalShift_modul2_C08

## Soal Nomor 1


## Soal Nomor 2


## Soal Nomor 3


## Soal Nomor 4

Untuk soal nomor 4 ini menggunakan daemon, yang mana saya menggunakan sesuai template yang ada di modul. Untuk *main program* kelompok kami, seperti di bawah ini.


```
    struct stat alamatMakanan;
    stat("/home/adam/SoalShift_modul2_C08/Soal4/Documents/makanan/makan_enak.txt", &alamatMakanan);
```

Stat disini digunakan untuk mengakses alamat file dari file yang akan kita cek dan disimpan di **alamatMakanan**. File yang akan di cek adalah makan_enak.txt apakah pernah dibuka setidaknya 30 detik yang lalu.

```
    if(difftime(time(NULL), alamatMakanan.st_atime) <= 30){
```
Syntax di atas digunakan untuk mengecek apakah file *makan_enak.txt* pernah dibuka setidaknya 30 detik yang lalu. Caranya dengan menghitung selisih antara waktu program C kita yang sedang berjalan sekarang dengan menggunakan **time(NULL)** dikurangi dengan waktu akses ketika membuka file *makan_enak.txt* dengan menggunakan **alamatMakanan.st_atime**. Jika selisihnya masih <= 30, maka file *makan_enak.txt* pernah dibuka dalam rentang 0 - 30 detik yang lalu.

``` 
    char makananCetak[100];
    strcpy(makananCetak, "/home/adam/SoalShift_modul2_C08/Soal4/Documents/makanan/makan_sehat");
```
Syntax di atas digunakan untuk menyimpan alamat file yang akan kita buat ketika file *makan_enak.txt* pernah dibuka dalam rentang waktu 0-30 detik yang lalu. Nama file yang dibuat adalah *makan_sehat#.txt*, dengan # menandakan urutan file yang telah kita buat dimulai dari 1. Syntax di atas masih menyimpan nama file *makan_sehat* untuk bagian berikutnya ada di bawah ini. Alamat file yang akan kita buat di simpan di dalam array of char dengan menggunakan *strcpy*.

    char waktu[5];
    sprintf(waktu, "%d", urutan);	

Syntax di atas digunakan untuk mengubah urutan file yang masih berupa *integer* menjadi bentuk *array of char* dengan menggunakan *sprintf*

```
    strcat(makananCetak, waktu);`
```

Syntax di atas untuk menggabungkan nama file yang kita buat yang terdapat di *array of char* **makananCetak** (hanya berisi alamat file hingga *makan_sehat*, belum terdapat urutan file ke berapa yang telah dibuat) dengan *array of char* **waktu** (hanya berisi urutan waktu untuk menghitung file *makan_sehat* yang telah dibuat). Sehingga ketika digabung maka keduanya akan tersimpan di *array of char* **makananCetak**.

```
    strcat(makananCetak, ".txt");
```

Syntax di atas untuk menggabungkan nama file yang kita buat dan urutan file (yang telah kita buat setelah proses *concat* sebelumnya) yang terdapat di *array of char* **makananCetak** (hanya berisi alamat file dan urutan file yang telah dibuat, belum terdapat ekstensi file yang akan dibuat) dengan **".txt"**(ekstensi file yang akan dibuat). Sehingga ketika digabung maka keduanya akan tersimpan di *array of char* **makananCetak**.

```
    FILE *filebaru = fopen(makananCetak, "w");
    fclose(filebaru);
```

Syntax di atas digunakan untuk membuat file baru dengan nama menggunakan yang terdapat di *array of char* **makananCetak** dan *w* (write) menandakan file tersebut sekaligus mengalami perubahan. Setelah itu menutup file yang telah kita buat.

```
    urutan++;
```

Syntax di atas digunakan untuk menandakan file *makan_sehat* yang telah kita buat

```
    sleep(5);
```
Syntax di atas digunakan agar program C yang kita buat berjalan setiap 5 detik.



## Soal Nomor 5



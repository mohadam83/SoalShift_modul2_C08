# SoalShift_modul2_C08

## Soal Nomor 1


## Soal Nomor 2
```
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>

int main() {
  pid_t pid, sid;

  pid = fork();

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();

  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while(1) {	
	DIR* folder; 
	chdir("/home/adam/SoalShift_modul2_C08/Soal2/hatiku/");	
	folder = opendir(".");
	if(folder == NULL){
	    perror("error");
	    return 0;	
	}
	else{
	    struct dirent* file;
	    file = readdir(folder);
	    char filename[200];
	    while(file!=NULL){
		for(int i = 0; i < strlen(file->d_name); i++){
		    filename[i] = file->d_name[i];		
		}
		if(strcmp(filename, "elen.ku")==0){
		    struct stat st = {0};
		    if(stat(filename, &st) < 0){
			perror("error");	continue;
		    }
		    struct group *grup_ = getgrgid(st.st_gid);	
		    struct passwd *owner_ = getpwuid(st.st_uid);
		    if(strcmp(grup_->gr_name,"www-data") == 0 && strcmp(owner_->pw_name,"www-data") == 0){
			if(chmod(filename, 0777) < 0){
			    perror("error");
			}
			remove(filename);
		    }    	
		}
	    }
	    closedir(folder);
	}
	sleep(3);
  }
  exit(EXIT_SUCCESS);
}
```
Untuk soal nomor 2 ini menggunakan daemon, yang mana saya menggunakan sesuai template yang ada di modul. Untuk *main program* kelompok kami, seperti di bawah ini.
```
DIR* folder; 
	chdir("/home/adam/SoalShift_modul2_C08/Soal2/hatiku/");	
	folder = opendir(".");
```
Syntax di atas digunakan untuk menyimpan alamat folder yang sedang kita akses yang memiliki file *elen.ku* sesuai soal dan disimpan di *folder* dengan tipe *DIR*.

```
	if(folder != NULL){
	    perror("error");
	    return 0;	
	}
```
Syntax di atas digunakan untuk mengecek jika tidak **NULL** maka proses akan berjalan. Jika tidak makan akan terdapat pesan *error* sesuai syntax di bagian *else* di bawah.

```
	struct dirent* file;
	file = readdir(folder);
```
Syntax di atas digunakan untuk menyimpan semua *file* yang ada di folder yang sedang kita akses sekarang untuk dilakukan proses iterasi hingga menemukan file *elen.ku*. Proses iterasinya ada di bawah ini.

```
	char filename[200];
	while(file!=NULL){
	    for(int i = 0; i < strlen(file->d_name); i++){
		filename[i] = file->d_name[i];
	    }
```
Syntax di atas digunakan untuk mengecek apakah nilai *file* NULL atau tidak, jika tidak maka proses akan lanjut untuk menyimpan nama file di *array of char* dengan nama *filename* untuk setiap iterasi.

```
	if(strcmp(filename, "elen.ku")==0){
	    struct stat st = {0};
	    if(stat(filename, &st) < 0){
		perror("error");	continue;
	    }
	    struct group *group_ = getgrgid(st.st_gid);	
	    struct passwd *owner_ = getpwuid(st.st_uid);
```

Syntax di atas digunakan untuk menyimpan data berupa owner dari file yang akan kita cek `**struct passwd *owner_ = getpwuid(st.st_uid);**` dan group dari file yang akan kita cek `** struct group *group_ = petgrgid(st.st_gid);**`.

```
	if(strcmp(group_->gr_name,"www-data") == 0 && strcmp(owner_->pw_name,"www-data") == 0){
   	    if(chmod(filename, 0777) < 0){
		perror("error");
	    }
	    remove(filename);
	}
```
Syntax di atas digunakan untuk mengecek apakah group dan owner dari file yang sedang kita cek yaitu *elen.ku* merupakan "www-data" dengan menggunakan `strcmp()` . Jika iya maka mengubah permission menjadi *0777* menggunakan *chmod* dan kemudian menghapus file yang akan kita hapus, yaitu yang tersimpan di *array of char* **filename**.

```
	    closedir(folder);
	}
	else{
	    perror("error");
	    return;	
	}
	sleep(3);
```
Syntax di atas digunakan untuk menutup *folder* yang telah kita akses sekarang dan *else* di atas jika *value* dari *folder* adalah **NULL**. Terakhir adalah `sleep(3)` digunakan agar file berjalan setiap 3 detik.

## Soal Nomor 3
```
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main() {
	pid_t proses1, proses2, proses3;
	int status;
	int simpan[2];

	if (pipe(simpan) < 0) {
	    return EXIT_FAILURE;
	}
	proses1 = fork();
	if (proses1 != 0) {
	    while((wait(&status)) > 0);
	    proses2 = fork();
	    if (proses2 != 0) {
		while((wait(&status)) > 0);
		proses3 = fork();
		if (proses3 == 0) {
		    char *array[] = {"touch", "daftar.txt", NULL};
		    execv("/usr/bin/touch", array);
		} else {
		    while((wait(&status)) > 0);
		    close(simpan[1]);
		    int bukaFileDaftar = open("daftar.txt", O_WRONLY);
		    dup2(bukaFileDaftar, STDOUT_FILENO);

		    dup2(simpan[0], STDIN_FILENO);

		    char *array[] = {"grep", ".txt$", NULL};
		    execv("/bin/grep", array);
		}
	    } 
	    else {
		close(simpan[0]);
		dup2(simpan[1], STDOUT_FILENO);

		char *array[] = {"ls", "campur2", NULL};
		execv("/bin/ls", array);
	    }    
	} 
	else {
	    char *array[] = {"unzip", "campur2.zip", NULL};
	    execv("/usr/bin/unzip", array);
	}
	return 0;
}
```

```
pid_t proses1, proses2, proses3;
int status;
int simpan[2];
```
Syntax di atas merupakan deklarasi variabel proses dengan tipe pid_t, sementara simpan[2] merupakan file descriptor adalah array yang mana indeks ke 0 merupakan output yang dihasilkan di console dan indeks ke 1 untuk mengalihkan output yang di console agar di tampung di file descriptor, yaitu dengan nama *simpan*.

```
proses1 = fork();
if (proses1 != 0) {
    while((wait(&status)) > 0);
    
} 
else {
    char *array[] = {"unzip", "campur2.zip", NULL};
    execv("/usr/bin/unzip", array);
}
```
Syntax di atas digunakan untuk menduplikasi proses, yang mana proses yang baru(child proses) ketika proses1 = 0 yaitu melakukan *unzip* terhadap file *campur2.zip*. Sementara *parent process* yaitu ketika proses1 != 0 terdapat proses lagi di dalamnya untuk memanggil proses baru yang dijelaskan di bawah ini, tetapi sebelum itu harus menunggu bahwa *child proses* telah dilakukan terlebih dahulu dengan menggunakan `while((wait(&status)) > 0);`.

```
proses2 = fork();
if (proses2 != 0) {
	while((wait(&status)) > 0);
} 
else {
	close(simpan[0]);
	dup2(simpan[1], STDOUT_FILENO);

	char *array[] = {"ls", "campur2", NULL};
	execv("/bin/ls", array);
}
```
Syntax di atas digunakan untuk menduplikasi proses dan syntax tersebut berada di bagian *parent process* dari proses1. Pada proses ini **(proses2)** kembali menggunakan `fork` dengan *child process* **proses2** nya adalah menduplikasi output yang dihasilkan dari proses menampilkan daftar file yang ada di folder **campur2** dengan menggunakan syntax berikut `(char *array[] = {"ls", "campur2", NULL}; execv("/bin/ls", array);)`. Untuk *parent process* dilakukan dengan menunggu *child process* telah dijalankan terlebih dahulu sehingga harus menunggu dengan menggunakan syntax `while((wait(&status)) > 0);`. Di dalam *parent process* proses2 ini terdapat proses lagi di dalamnya yang akan dijelaskan di bagian bawah ini.

```
proses3 = fork();
if (proses3 == 0) {
    char *array[] = {"touch", "daftar.txt", NULL};
    execv("/usr/bin/touch", array);
} else {
    while((wait(&status)) > 0);
    close(simpan[1]);
    int bukaFileDaftar = open("daftar.txt", O_WRONLY);
    dup2(bukaFileDaftar, STDOUT_FILENO);

    dup2(simpan[0], STDIN_FILENO);

    char *array[] = {"grep", ".txt$", NULL};
    execv("/bin/grep", array);
}
```
Syntax di atas terdapat di *parent process* dari **proses2** yang mana dilakukan duplikasi proses kembali dengan menggunakan `fork` dan dipanggil dari variabel **proses3**. Untuk *child process* dari **proses3** ini adalah melakukan pembuatan file baru dengan nama *daftar.txt* menggunakan `touch` dan `execv` seperti pada tampilan syntax di atas di bagian ketika `**proses3** = 0` *(child process)*. Sedangkan di *parent process* dari **proses3** ini adalah membuka file *daftar.txt* yang telah dibuat di *child process* kemudian pada file yang telah dibuka tersebut di isi (*write*) dengan nama-nama file yang ada di *file descriptor* **simpan**, tetapi tidak semua dari nama file tersebut langsung diisi ke file *daftar.txt*, namun hanya yang bertipe *.txt* sesuai permintaan di soal dengan menggunakan syntax *grep* seperti berikut `char *array[] = {"grep", ".txt$", NULL}; execv("/bin/grep", array);`.

## Soal Nomor 4
```
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <time.h>
#include <string.h>

int main() {
  pid_t pid, sid;

  pid = fork();

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();

  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  int urutan = 1;

  while(1) {
    struct stat alamatMakanan;
    stat("/home/adam/SoalShift_modul2_C08/Soal4/Documents/makanan/makan_enak.txt", &alamatMakanan);
    if(difftime(time(NULL), alamatMakanan.st_atime) <= 30){ 
	char makananCetak[100];
	strcpy(makananCetak, "/home/adam/SoalShift_modul2_C08/Soal4/Documents/makanan/makan_sehat");
	char waktu[5];
	sprintf(waktu, "%d", urutan);
	strcat(makananCetak, waktu);
	strcat(makananCetak, ".txt");
	FILE *filebaru = fopen(makananCetak, "w");
	fclose(filebaru);
	urutan++;
    }
    sleep(5);
  }
  exit(EXIT_SUCCESS);
}
```

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



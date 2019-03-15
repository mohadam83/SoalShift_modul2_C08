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

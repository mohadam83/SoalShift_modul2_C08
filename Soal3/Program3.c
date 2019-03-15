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

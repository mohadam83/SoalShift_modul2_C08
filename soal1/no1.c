#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
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

    while(1)
    {
        char folder[40];
        strcpy(folder, "/home/elang/modul2/");

        char gambar[40];
        strcpy(gambar, "/home/elang/modul2/gambar/");

        char file[30];
        //char file2[30];
        //char file3[30];
        char baru[30] = "_grey.png";
        char *ext;
       // char a = '\0';
        DIR *openfile;

        struct dirent *dir;
        openfile = opendir(folder);

        if (openfile)
        {
            while ((dir = readdir(openfile)) != NULL)
            {
                // strcpy(folder2, "/home/salsha/modul2/gambar/");
                // strcpy(folder1, "/home/salsha/modul2/");
                //strcpy(file, dir->d_name);
                ext = strrchr(dir->d_name, '.');
                //strcpy(file3, file);
                if((strcmp(ext, ".png") == 0) && ext)
                {
                    *ext = '\0';
                    strcpy(file, dir->d_name);
                    strcat(file, baru);
                    strcat(gambar, file);
                    strcat(folder, dir->d_name);
                    rename(folder, gambar);
                }
            }
            closedir(openfile);
        }
        sleep(1);
    }
    exit(EXIT_SUCCESS);
}

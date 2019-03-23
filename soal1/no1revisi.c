#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>

int main()
{
    pid_t pid, sid;
    pid=fork();
    if (pid < 0){
        exit(EXIT_FAILURE);
    }
    if (pid > 0){
        exit(EXIT_SUCCESS);
    }
    umask(0);
    sid = setsid();
    if(sid<0){
        exit(EXIT_FAILURE);
    }

    if((chdir("/"))<0) {
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDERR_FILENO);
    close(STDOUT_FILENO);

    while(1)
    {           
        char folder[100];
        strcpy(folder, "/home/salsha/modul2/");

        char gambar[100];
        strcpy(gambar, "/home/salsha/modul2/gambar/");

        char *cek, *file, file2[100];
        DIR *openfolder;

        struct dirent *dir;
        openfolder = opendir(folder);
        
        if (openfolder)
        {
            while ((dir = readdir(openfolder)) != NULL)
            {
                strcpy(folder, "/home/salsha/modul2/");
                strcpy(gambar, "/home/salsha/modul2/gambar/");

                //printf("%s\n%s\n", folder, gambar);

                cek = strstr(dir->d_name, ".png"); //cek substring

                if(cek)
                {
                    strcpy(file2, "");

                    file = strtok(dir->d_name, ".");
                    strcat(file2, file);
                    while(file != NULL){
                        file = strtok(NULL, ".");
                        if(strcmp(file, "png") == 0) {
                            break;
                        }
                        else {
                            strcat(file2, ".");
                            strcat(file2, file);
                        }
                    }
                   // printf("%s\n", file);

                    strcat(folder, file2);
                    strcat(folder, ".png");
                   // printf("%s\n", folder);
                    strcat(gambar, file2);
                    strcat(gambar, "_grey.png");
                    rename(folder, gambar);
                    //rename("/home/salsha/modul2/tebe.png", "/home/salsha/modul2/gambar/tebe_grey.png")
                   // printf("%s\n%s\n", gambar, folder);
                }
            }
        }
        closedir(openfolder);
        sleep(1);
    }
    exit(EXIT_SUCCESS);
}

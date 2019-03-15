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
    int menit = 0;
    while(1) {
        time_t rawtime;
        struct tm *info;
        char waktu[50], folder[100];
        time(&rawtime);
        info = localtime(&rawtime);
        strftime(waktu, sizeof(waktu), "%d:%m:%Y-%H:%M", info); 
        if(menit%30==0){
            sprintf(folder, "/home/salsha/log/%s/", waktu);
            mkdir(folder, 0777);
        }
        int no = menit+1;
        char file[33], foldercpy[100];
	strcpy(foldercpy,folder);
        //strcpy(file, "");
        sprintf(file, "log%d.log", no);
        strcat(foldercpy,file);
        
        FILE *flog, *ffile;
        ffile = fopen(foldercpy,"w");
        flog = fopen("/var/log/syslog", "r");
       
        char log[8000];

        if (flog != NULL){
            if (ffile != NULL){
                while ( fgets (log, 8000 , flog) != NULL ) fputs (log, ffile);
                fclose (ffile);
            }
            fclose (flog);
        }
        sleep(60);
        menit++;
    }
    exit(EXIT_SUCCESS);
}


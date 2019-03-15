#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>

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
	DIR* folder = opendir("/home/adam/SoalShift_modul2_C08/Soal2/hatiku/");	
	if(folder == NULL){
	    perror("error");
	    return;	
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
		    struct group *group_ = petgrgid(st.st_gid);	
		    struct passwd *owner_ = getpwuid(st.st_uid);
		    char ubahpermission[5];
		    strcpy(ubahpermission, "0777");
		    if(strcmp(group_->gr_name,"www-data") == 0 && strcmp(owner_->pw_name,"www-data") == 0){
			if(chmod(filename, ubahpermission) < 0){
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

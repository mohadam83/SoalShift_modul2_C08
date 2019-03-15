#include <sys/types.h>
#include <unistd.h>

int main()
{
    char *argv[3] = {"pkill", "no5a", NULL};
    execv("/usr/bin/pkill", argv);
}
 

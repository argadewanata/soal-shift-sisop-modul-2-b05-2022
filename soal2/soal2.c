#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>
#include <syslog.h>
#include <string.h>

int main()
{
    char* path = "/home/drakor";
    pid_t child_id1;
    pid_t child_id2;
    pid_t child_id3;

    child_id1 = fork();
    if (child_id1 == 0)
    {
        char *argv[] = {"mkdir", "-p", "/home/argadewanata/shift2/drakor",NULL};
        execv("/bin/mkdir", argv);
    }

    child_id2 = fork();
    if (child_id2 == 0)
    {
        sleep(2);
        char *argv[]={"unzip","drakor.zip","-d","/home/argadewanata/shift2/drakor/",NULL};
        execv("/bin/unzip", argv);
    }

    child_id3 = fork();
    if(child_id3 == 0)
    {
        sleep(3);
        char *argv[] = {"rm ", "-rf ", "/home/argadewanata/shift2/drakor/coding", "/home/argadewanata/shift2/drakor/song", "/home/argadewanata/shift2/drakor/trash",NULL};
		execv("/bin/rm", argv);
    }
}



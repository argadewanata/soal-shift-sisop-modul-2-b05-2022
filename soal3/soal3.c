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

int main ()
{
    pid_t child_id1;
    pid_t child_id2;
    pid_t child_id3;
    int status;

    /*
        Nomor 3A :  
        Membuat dir  "/home/[USER]/modul2/darat”  lalu 3 detik kemudian  membuat  dir  "home/[USER]/modul2/air”
    */
    child_id1 = fork();
    if (child_id1 < 0)
    {
        exit(EXIT_FAILURE);
    }

    else if(child_id1 == 0)
    {
        char *argv[] = {"mkdir", 
                                        "-p",
                                         "/home/argadewanata/modul2/darat", 
                                         NULL};
        execv("/bin/mkdir", argv);
    } 

    child_id2 = fork();
    if (child_id2 < 0)
    {
        exit(EXIT_FAILURE);
    }

    else if(child_id2 == 0)
    {
        sleep(3);
        char *argv[] = {"mkdir", 
                                        "-p", 
                                        "/home/argadewanata/modul2/air",
                                         NULL};
        execv("/bin/mkdir", argv);
    }

    /*
        Nomor 3B:
        Melakukan unzip  pada file "animal.zip" ke directory "/home/argadewanata/modul2/"
    */

   child_id3 = fork();
   if(child_id3< 0)
    {
        exit(EXIT_FAILURE);
    }

    else if(child_id3 == 0)
    {
        char *argv[] = {"unzip", 
                                     "animal.zip", 
                                     "-d", 
                                     "/home/argadewanata/modul2/", 
                                     NULL};
        execv("/bin/unzip", argv);
    }

    return 0;
}
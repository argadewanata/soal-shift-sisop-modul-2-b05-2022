#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <dirent.h>
#include <signal.h>
#include <wait.h>
#include <pwd.h>
#include <grp.h>
#include <sys/wait.h>
#include <syslog.h>

int main ()
{
    pid_t child_createdir_darat;
    pid_t child_createdir_air;
    pid_t child_move_air;
    pid_t child_remove;
    pid_t child_unzip;

    int status;

    /*
        Nomor 3A :  
        Membuat dir  "/home/[USER]/modul2/darat”  lalu 3 detik kemudian  membuat  dir  "home/[USER]/modul2/air”
    */

    child_createdir_darat = fork();
    if (child_createdir_darat < 0)
    {
        exit(EXIT_FAILURE);
    }
    else if(child_createdir_darat ==0)
    {
        char *argv[] = {"mkdir", "-p", "/home/argadewanata/modul2/darat",NULL};
        execv("/bin/mkdir", argv);
    }

    child_createdir_air = fork();
    if (child_createdir_air < 0)
    {
        exit(EXIT_FAILURE);
    }

    else if(child_createdir_air == 0)
    {
        sleep(3);
        char *argv[] = {"mkdir", "-p","/home/argadewanata/modul2/air", NULL};
        execv("/bin/mkdir", argv);
    } 

    /*
        Nomor 3B:
        Melakukan unzip  pada file "animal.zip" ke directory "/home/argadewanata/modul2/"
    */
    child_unzip = fork();
    if (child_unzip < 0)
    {
        exit(EXIT_FAILURE);
    }
    
    else if(child_unzip == 0)
    {
        char *argv[] = {"unzip", "animal.zip", "-d", "/home/argadewanata/modul2/", NULL};
        execv("/bin/unzip", argv);
    }
    else 
    {
        /*
            Nomor 3C:
            Hasil extract  dipisah sesuai  dengan nama filenya. Jika hewan darat maka dimasukkan ke folder darat dan jika hewan
            air maka
            dimasukkan ke folder air.  JApabila terdapat hewan yang tidak ada keterangan maka dihapus
        */
        while((wait(&status)) > 0);
        
        DIR *directory;
        struct dirent *ep;

        char source1[150] ;
        strcpy(source1,"/home/argadewanata/modul2/animal");
        char source2[150] ;
        strcpy(source2,"/home/argadewanata/modul2/animal/");
        char dest_darat[150];
        strcpy(dest_darat,"/home/argadewanata/modul2/darat");
        char dest_air[150] ;
        strcpy(dest_air,"/home/argadewanata/modul2/air");

        char file_darat[25];
        char file_air[25];
        char file_lain[25];

        pid_t child_move_darat;
        pid_t child_move_air;
        pid_t child_remove;

        directory = opendir(source1);
    
        if(directory != NULL)
        {
            while((ep = readdir(directory)))
            {
                if(strstr(ep->d_name,"darat") != NULL) //  apabila kata "darat" ada
                {
                    memset(file_darat,0,strlen(file_darat));
                    strcat(file_darat,source2);
                    strcat(file_darat,ep->d_name);

                    child_move_darat = fork();
                    if(child_move_darat < 0 )
                    {
                        exit(EXIT_FAILURE);
                    }

                    else if(child_move_darat == 0)
                    {
                        char *argv[] = {"mv",file_darat,dest_darat,NULL};
                        execv("/bin/mv", argv);
                    }
                }
                else if (strstr(ep->d_name,"air") != NULL) //  apabila kata "air" ada
                {
                    memset(file_air,0,strlen(file_air));
                    strcat(file_air,source2);
                    strcat(file_air,ep->d_name);

                    child_move_air= fork();
                    if(child_move_air < 0 )
                    {
                        exit(EXIT_FAILURE);
                    }
                    else if (child_move_air == 0)
                    {
                        char *argv[] = {"mv",file_air,dest_air,NULL};
                        execv("/bin/mv", argv);
                    }
                } 
                else  // Kondisi ketika tidak ada keterangan darat atau air
                {
                    memset(file_lain,0,strlen(file_lain));
                    strcat(file_lain,source2);
                    strcat(file_lain,ep->d_name);

                    child_remove = fork();
                    if(child_remove < 0 )
                    {
                        exit(EXIT_FAILURE);
                    }

                    else if (child_remove == 0)
                    {
                        char *argv[] = {"rm", file_lain, NULL};
                        execv("/bin/rm", argv);
                    }
                } 
            }         
        }

        /*
            Nomor 3D:
            Menghapus semua  gambar burung  yang ditandai dengan kata "bird " pada nama file
        */
        
        pid_t child_remove_bird;
        child_remove_bird = fork();

        if(child_remove_bird  < 0) 
        {
            exit(EXIT_FAILURE);
        }
        else if (child_remove_bird == 0)
        {
            execl("/bin/sh", "sh", "-c", "rm -f/home/argadewanata/modul2/darat/*bird*", (char *) NULL);
        } 
        else 
        {
            while((wait(&status)) > 0);
        }

        /*
            Nomor 3E:
            Membuat  list .txt yang berisi list nama hewan dengan format UID_[UID file permission]_Nama File.[jpg/png]
            pada folder air 
        */

        char path_list[100];
        strcpy(path_list,"/home/argadewanata/modul2/air/list.txt");
        char source_air1[100];
        strcpy(source_air1,"/home/argadewanata/modul2/air");

        char userID[130];
        char templateList[550] ;

        DIR *directory2;
        struct dirent *ep2;
        struct stat fs;

        FILE *file = fopen(path_list, "a");
        directory2 = opendir(source_air1);
        
        while(ep2= readdir(directory2)) 
        {
            char filePermission[50] ="";   
            char path[100] = "/home/argadewanata/modul2/air/";
            
            cuserid(userID);
            strcat(path, ep2->d_name);
            
            int r = stat(path, &fs);
            
            // Agar  direktroi . dan .. tidak termasuk 
            if(!(S_ISREG(fs.st_mode) && strcmp(ep2->d_name, "list.txt")!=0)) 
            {
                continue;
            }
                
            if(fs.st_mode & S_IRUSR) 
            {
                strcat(filePermission, "r");
            }
                
            if(fs.st_mode & S_IWUSR) 
            {
                strcat(filePermission, "w");
            }
                
            if(fs.st_mode & S_IXUSR) 
            {
                strcat(filePermission, "x");
            }
                
            sprintf(templateList, "%s_%s_%s\n", userID, filePermission, ep2->d_name);
            fprintf(file, templateList);
        }
        
        fclose(file);
       
    }
    return 0;
}

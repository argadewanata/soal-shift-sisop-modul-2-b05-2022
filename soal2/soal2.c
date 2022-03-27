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
     /*
        Mengekstrak drakor.zip ke dalam folder â€œ/home/[user]/shift2/drakorâ€ dan menghapus folder yang ikut terekstrak 
    */
    pid_t child_id1;
    pid_t child_id2;
    pid_t child_id3;
    int status;
 
    child_id1 = fork();
    if (child_id1 == 0)
    {
        char *argv[] = {"mkdir", "-p", "/home/noob/shift2/drakor",NULL};
        execv("/bin/mkdir", argv);
    }
 
    child_id2 = fork();
    if (child_id2 == 0)
    {
        sleep(2);
        char *argv[]={"unzip", "/home/noob/drakor/drakor.zip","-d","/home/noob/shift2/drakor/",NULL};
        execv("/bin/unzip", argv);
    }
 
    child_id3 = fork();
    if(child_id3 == 0)
    {
        sleep(3);
        char *argv[] = {"rm ", "-rf", "/home/noob/shift2/drakor/coding", "/home/noob/shift2/drakor/trash", "/home/noob/shift2/drakor/song",  NULL};
		execv("/bin/rm", argv);
    }
 
    /*
        Membuat folder kategori  dan memasukkan drakor sesuai kategorinya
    */
    pid_t child_createdir_thriller;
    pid_t child_createdir_horror;
    pid_t child_createdir_action;
    pid_t child_createdir_comedy;
    pid_t child_createdir_romance;
    pid_t child_createdir_school;
    pid_t child_createdir_fantasy;
 
    char folder_thriller[50] = "/home/noob/shift2/drakor/thriller";
    char folder_horror[50] = "/home/noob/shift2/drakor/horror";
    char folder_action[50] = "/home/noob/shift2/drakor/action";
    char folder_comedy[50] = "/home/noob/shift2/drakor/comedy";
    char folder_romance[50] = "/home/noob/shift2/drakor/romance";
    char folder_school[50] = "/home/noob/shift2/drakor/school";
    char folder_fantasy[50] = "/home/noob/shift2/drakor/fantasy";
 
    // Membuat Folder Thriller
    child_createdir_thriller= fork();
    if (child_createdir_thriller < 0 )
    {
        exit(EXIT_FAILURE);
    }
    else if (child_createdir_thriller == 0 )
    {
        char *argv[] = {"mkdir", "-p", folder_thriller,NULL};
        execv("/bin/mkdir", argv);
    }
 
    // Membuat Folder Horror
    child_createdir_horror= fork();
    if (child_createdir_horror < 0 )
    {
        exit(EXIT_FAILURE);
    }
    else if (child_createdir_horror == 0 )
    {
        char *argv[] = {"mkdir", "-p", folder_horror,NULL};
        execv("/bin/mkdir", argv);
    }
 
    // Membuat Folder Action
    child_createdir_action= fork();
    if (child_createdir_action< 0 )
    {
        exit(EXIT_FAILURE);
    }
    else if (child_createdir_action == 0 )
    {
        char *argv[] = {"mkdir", "-p", folder_action,NULL};
        execv("/bin/mkdir", argv);
    }
 
    // Membuat Folder Comedy
    child_createdir_comedy= fork();
    if (child_createdir_comedy< 0 )
    {
        exit(EXIT_FAILURE);
    }
    else if (child_createdir_comedy == 0 )
    {
        char *argv[] = {"mkdir", "-p", folder_comedy,NULL};
        execv("/bin/mkdir", argv);
    }
 
    // Membuat Folder Romance
    child_createdir_romance= fork();
    if (child_createdir_romance< 0 )
    {
        exit(EXIT_FAILURE);
    }
    else if (child_createdir_romance == 0 )
    {
        char *argv[] = {"mkdir", "-p", folder_romance,NULL};
        execv("/bin/mkdir", argv);
    }
 
    // Membuat Folder School
    child_createdir_school= fork();
    if (child_createdir_school< 0 )
    {
        exit(EXIT_FAILURE);
    }
    else if (child_createdir_school== 0 )
    {
        char *argv[] = {"mkdir", "-p", folder_school,NULL};
        execv("/bin/mkdir", argv);
    }
 
    // Membuat Folder Fantasy
    child_createdir_fantasy= fork();
    if (child_createdir_fantasy< 0 )
    {
        exit(EXIT_FAILURE);
    }
    else if (child_createdir_fantasy== 0 )
    {
        char *argv[] = {"mkdir", "-p", folder_fantasy,NULL};
        execv("/bin/mkdir", argv);
    }

        /*
        Memindahkan poster ke dalam folder yang telah dibuat sekaligus mengubah namanya
    */  
 
    pid_t child_move_thriller;
    pid_t child_move_horror;
    pid_t child_move_action;
    pid_t child_move_comedy;
    pid_t child_move_romance;
    pid_t child_move_school;
    pid_t child_move_fantasy;
 
    char default_path[50] = "/home/noob/shift2/drakor";
 
    // Memindahkan ke Folder Thriller
    child_move_thriller= fork();
    if (child_move_thriller < 0 )
    {
        exit(EXIT_FAILURE);
    }
    else if (child_move_thriller == 0 )
    {
        char *argv[] = {"find", default_path, "-type", "f", "-iname", "*thriller*", "-exec", "mv", "{}", folder_thriller, ";", NULL};
		execv("/bin/find", argv);
    }
    else
    {
        while(wait(&status) > 0 );
    }
    // Memindahkan ke Folder horrir
    child_move_horror= fork();
    if (child_move_horror < 0 )
    {
        exit(EXIT_FAILURE);
    }
    else if (child_move_horror == 0 )
    {
        char *argv[] = {"find", default_path, "-type", "f", "-iname", "*horror*", "-exec", "mv", "{}", folder_horror, ";", NULL};
		execv("/bin/find", argv);
    }
    else
    {
        while(wait(&status) > 0 );
    }
    // Memindahkan ke Folder school
    child_move_school= fork();
    if (child_move_school < 0 )
    {
        exit(EXIT_FAILURE);
    }
    else if (child_move_school == 0 )
    {
        char *argv[] = {"find", default_path, "-type", "f", "-iname", "*school*", "-exec", "mv", "{}", folder_school, ";", NULL};
		execv("/bin/find", argv);
    }
    else
    {
        while(wait(&status) > 0 );
    }
     // Memindahkan ke Folder fantasy
    child_move_fantasy= fork();
    if (child_move_fantasy < 0 )
    {
        exit(EXIT_FAILURE);
    }
    else if (child_move_fantasy == 0 )
    {
        char *argv[] = {"find", default_path, "-type", "f", "-iname", "*fantasy*", "-exec", "mv", "{}", folder_fantasy, ";", NULL};
		execv("/bin/find", argv);
    }
    else
    {
        while(wait(&status) > 0 );
    }
    // Memindahkan ke Folder romance
    child_move_romance= fork();
    if (child_move_romance < 0 )
    {
        exit(EXIT_FAILURE);
    }
    else if (child_move_romance == 0 )
    {
        char *argv[] = {"find", default_path, "-type", "f", "-iname", "*romance*", "-exec", "mv", "{}", folder_romance, ";", NULL};
		execv("/bin/find", argv);
    }
    else
    {
        while(wait(&status) > 0 );
    }
    // Memindahkan ke Folder comedy
    child_move_comedy= fork();
    if (child_move_comedy < 0 )
    {
        exit(EXIT_FAILURE);
    }
    else if (child_move_comedy == 0 )
    {
        char *argv[] = {"find", default_path, "-type", "f", "-iname", "*comedy*", "-exec", "mv", "{}", folder_comedy, ";", NULL};
		execv("/bin/find", argv);
    }
    else
    {
        while(wait(&status) > 0 );
    }
    // Memindahkan ke Folder action
    child_move_action= fork();
    if (child_move_action < 0 )
    {
        exit(EXIT_FAILURE);
    }
    else if (child_move_action == 0 )
    {
        char *argv[] = {"find", default_path, "-type", "f", "-iname", "*action*", "-exec", "mv", "{}", folder_action, ";", NULL};
		execv("/bin/find", argv);
    }
    else
    {
        while(wait(&status) > 0 );
    }

    return 0;
}


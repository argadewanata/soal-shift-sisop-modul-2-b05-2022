#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <wait.h>
#include <time.h>
#include <json-c/json.h>
#include <dirent.h>


int g_rand(int max);
void downld(char *url, char *filename);
char *url_chara = "https://drive.google.com/u/0/uc?id=1xYYmsslb-9s8-4BDvosym7R4EmPi6BHp&export=download";
char *url_weap = "https://drive.google.com/u/0/uc?id=1XSkAqqjkNmzZ0AdIZQt_eWGOZ0eJyNlT&export=download";

void create_dir(char *dirname);
void d_dir(char dir[100]);

void unzp(char *filename);
void zp_fd();

int primogems = 79000;
void gacha(int count, char cur_dir[100]);
void prims(int *primo);

void end();

int main() {
    pid_t pid, sid; //set tempat pid

    pid = fork();     //set di child

    // fork pid < 0 maka keluar
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

    if ((chdir("/home/noob/sisop/mod2/soal1")) < 0) {
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    downld(url_chara, "characters.zip"); 
    downld(url_weap, "weapons.zip");
    unzp("characters.zip"); 
    unzp("weapons.zip");
    create_dir("gacha_gacha");
    int tot_gacha = 0; 

    while (1) {
        time_t timer;
        char template_time[100];
        struct tm *tm_info;
        timer = time(NULL);
        tm_info=localtime(&timer);
        strftime(template_time, 100, "%H:%M:%S", tm_info);
        int round_ten = tot_gacha - (tot_gacha%10);
        char number[5], cur_dir[100];
        sprintf(number,"%d",round_ten);
        strcpy(cur_dir,"gacha_gacha/");
        strcat(cur_dir,template_time);
        strcat(cur_dir, "_gacha_");
        strcat(cur_dir, number);
        strcat(cur_dir, ".txt");
        
        for (size_t i = 0; i < 10; i++)
        {
            tot_gacha++;
            prims(&primogems);
            gacha(tot_gacha, cur_dir);
        }
        sleep(1);
        srand(time(NULL));
    }
}

void downld(char *url, char *filename){
    pid_t id_child;
    id_child = fork();
    
    if(id_child == 0){
        char *argv[] = {"wget","-q", "--no-check-certificate", url, "-O", filename, NULL};
        execv("/bin/wget", argv);
        exit(EXIT_SUCCESS);
    }
    else if(id_child > 0) {
        wait(NULL);
    }
}

void unzp(char *filename){
    pid_t id_child;
    id_child = fork();
    
    if (id_child == 0) {
        char *argv[] = {"unzip", "-n", "-q", filename, NULL};
        execv("/bin/unzip", argv);
        exit(EXIT_SUCCESS);
    }
    else if (id_child > 0) {
        wait(NULL);
    }
}

void create_dir(char *dirname) {
    pid_t id_child;
    id_child = fork();
    
    if (id_child == 0) {
        DIR *dir = opendir(dirname);
        if (dir)
        {
            closedir(dir);
        } else {
        char *argv[] = {"mkdir", dirname, NULL};
        execv("/bin/mkdir",argv);
        }
        exit(EXIT_SUCCESS);
    }
    else if (id_child > 0) {
        wait(NULL);
    }
}

int g_rand(int max){
    
    return (rand() % max);
}
void prims(int *primo){
    *primo = *primo - 160;
    if(*primo <= 160){
       zp_fd(); 
       d_dir("gacha_gacha");
       d_dir("weapons");
       d_dir("characters");
       end();
    }
}
void end(){
    exit(EXIT_SUCCESS);
}
void d_dir(char dir[100]){
    pid_t id_child;
    id_child = fork();
    
    if (id_child == 0) {
        char *argv[] = {"rm","-rf", dir, NULL};
        execv("/bin/rm",argv);
        exit(EXIT_SUCCESS);
    }
    else if (id_child > 0) {
        wait(NULL);
    }
}
void zp_fd(){
    pid_t id_child;
    id_child = fork();
    
    if (id_child == 0) {
        char *argv[] = {"zip", "-q", "-r", "-P", "satuduatiga", "not_safe_for_wibu.zip", "gacha_gacha", NULL};
        execv("/bin/zip",argv);
        exit(EXIT_SUCCESS);
    }
    else if (id_child > 0) {
        wait(NULL);
    }
}

void gacha(int count, char cur_dir[100]){ 

    int max;
    char path[100];
    DIR *dp;
    struct dirent *ep;
    char path_r[100];
    char ty_item[100];

    if(count%2==0){
        max = 130;
        strcpy(ty_item,"Weapons");
        strcpy(path, "weapons/");
    } else {
        max = 48;
        strcpy(ty_item,"Characters");
        strcpy(path, "characters/");
    } 
    dp = opendir(path);

    int random = g_rand(max);
    if(dp != NULL)
    {
        for (int j = 0; j <= random; j++){
            ep = readdir(dp);
        }
        strcpy(path_r, ep->d_name);
        ep = NULL;
        closedir(dp);
    } else {
        perror("Can't Open Directory");
    }
    // Baca json
    strcat(path, path_r);
    char buffer[4096];
    struct json_object *parsed_json;
    struct json_object *rarity;
    struct json_object *name;
    FILE *fp;

    fp = fopen(path, "r");
    fread(buffer, 4096, 1, fp);
    fclose(fp);

    parsed_json = json_tokener_parse(buffer);
    json_object_object_get_ex(parsed_json, "name", &name);
    json_object_object_get_ex(parsed_json, "rarity", &rarity);

    FILE *gacha_file;
    char insert_into_file[100];
    char num[5], primo[10];
    sprintf(num, "%d",count);
    sprintf(primo, "%d",primogems);

    gacha_file = fopen(cur_dir, "a");

    strcpy(insert_into_file,num);
    strcat(insert_into_file,"_");
    strcat(insert_into_file,ty_item);
    strcat(insert_into_file,"_");
    strcat(insert_into_file,json_object_get_string(rarity));
    strcat(insert_into_file,"_");
    strcat(insert_into_file,json_object_get_string(name));
    strcat(insert_into_file,"_");
    strcat(insert_into_file,primo);
    strcat(insert_into_file,"\n");

    fputs(insert_into_file,gacha_file);
    fclose(gacha_file);
}

# Laporan Resmi Praktikum Modul 2 Kelompok B05 Sistem Operasi B Tahun 2022

Kelompok B05 Sistem Operasi B Tahun 2022

Nama Lengkap | NRP
------------- | -------------
Fahmi Muhazir        | 5025201043
Sidrotul Munawaroh   | 5025201047
Rere Arga Dewanata   | 5025201078 

## Jawaban Soal 1 (Sesi Revisi)
## Soal 1
Mas Refadi adalah seorang wibu gemink.Dan jelas game favoritnya adalah bengshin impek. Terlebih pada game tersebut ada sistem gacha item yang membuat orang-orang selalu ketagihan untuk terus melakukan nya. Tidak terkecuali dengan mas Refadi sendiri. Karena rasa penasaran bagaimana sistem gacha bekerja, maka dia ingin membuat sebuah program untuk men-simulasi sistem history gacha item pada game tersebut. Tetapi karena dia lebih suka nge-wibu dibanding ngoding, maka dia meminta bantuanmu untuk membuatkan program nya. Sebagai seorang programmer handal, bantulah mas Refadi untuk memenuhi keinginan nya itu. 

## Penyelesaian soal 1
### 1a
Pada poin ini kita diminta untuk mendownload file yang menjadi data untuk melakukan proses gacha <br>
Berikut adalah kode untuk mendownload dari url yang diberikan. <br>
```c
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

```
Penjelasan kode:
- `pid_t id_child` adalah untuk mengembalikan process ID dari proses saat ini.
- `id_child = fork()` forking kepada id proses yang berjalan. 
- `if(id_child == 0)` adalah jika proses adalah `child`, maka akan masuk `if`.
- `char *argv[]` untuk menampung kata-kata sesuai yang tertulis command line untuk dijadikan parameter pada fungsi `execv()`.
- `execv("/bin/wget, argv")` menjalankan fungsi `wget` dengan parameter yang ada di variable `argv`.
- `else if (id_child > 0)` jika parent, maka masuk else.
- `wait(NULL)` adalah sintaks untuk menunggu hingga child selesai mengeksekusi programnya.

File yang telah di download akan diunzip sesuai dengan ketentuan soal. <br>
Berikut adalah kode untuk meng-unzip dari nama file yang diberikan.
```c
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

```
- penjelasan nya mirip dengan saat mengeksekusi function download namun tujuan program ini adalah unzip
<br>

Selanjutnya, kita diminta untuk membuat direktori yang bernama `gacha_gacha`.
Berikut adalah kode untuk membuat direktori.
```c
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


```
- `DIR *dir = opendir(dirname)` adalah untuk mengecek apakah sudah ada direktori bernama `dirname`, jika ada maka lakukan `closedir()` juga `exit`.
<br>


### 1b, 1c, dan 1d
Terdapat ketentuan gacha seperti berikut:
- Jika counter gacha adalah genap, maka hasilnya adalah `weapons`. Jika ganjil, maka `characters`. 
- Untuk setiap counter gacha kelipatan 10, maka hasil tersebut akan dimasukkan kedalam file dengan format nama `{hh:mm:ss}_gacha_{jumlah-gacha}.txt`. Jarak pembuatan antar file berjarak 1s.
- Untuk setiap counter gacha kelipatan 90, maka hasil tersebut akan dimasukkan kedalam folder dengan format nama `tot_gacha{jumlah-gacha}`.


Berikut adalah kode untuk program gacha pada `int main()`.
```c
int total_gacha = 0;
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

```
- `char cur_dir[100]` untuk membuat format direktori sesuai ketentuan `tot_gacha{jumlah-gacha}`.
- `sprintf(num_dir, "%d", round_nine)` memformat int `round_nine` kedalam string lalu disimpan didalam variable `num_dir`.
- `for (int j = 0; j < 9; j++)` untuk looping per 1 folder (kelipatan 90).
- `time_t timer` untuk menggunakan fungsi `localtime()` kedepannya.
- `timer = time(NULL)` inisialisasi timer.
- `struct tm *tm` struct untuk memformat time menjadi struct
- `strftime(template_time, 100, "%H:%M:%S", tm_info)` memformat `datetime` sesuai format soal dan menyimpannya kedalam `formatted_time`.
- `for (int i = 0; i < 10; i++)` untuk looping per 10 gacha yang akan dimasukkan kedalam 1 file .txt.
- `srand(time(NULL))` untuk mereset `rand()` (didalam function `g_rand()`).


Fungsi ini akan dijalankan setiap kali fungsi `gacha()` akan dipanggil. Fungsi ini akan mengurangi `primogems` hingga dibawah batas gacha yaitu 160. <br>
Jika nilai `primogems` dibawah 160, maka program akan menunggu hingga waktu yang ditentukan. Penjelasan lebih lanjut akan diberikan di poin 1e.

Untuk kode dari function `gacha()` adalah sebagai berikut.
```c

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

```
Dengan parameter `count` berupa total gacha yang sudah diakukan dan `cur_dir[100]` untuk path ke file yang diinginkan.
- Variable `max`, `item_type`, dan `path` merupakan jumlah file yang ada di folder `weapons/` ataupun `characters/`. Nilai kedua variable tersebut akan diisi bergantung dari variable `count`. Jika `count` adalah genap, maka set dengan ketentuan dari `Weapons`. Dan jika genap, isi dengan ketentuan dari `Characters`.
- `max` adalah jumlah dari file pada path tertentu (untuk `weapons/` adalah 130, dan untuk `characters/` adalah 48). Ditentukan secara manual.
- Terdapat `struct json_object` untuk menampung hasil json dari file .json yang diambil. Terdapat juga beberapa fungsi header `<json-c/json.h>` seperti mengambil hasil, mem-parse string json, dan lainnya.
- Pada bagian terakhir dari kode berfungsi untuk menuliskan hasil gacha sesuai format `{jumlah-gacha}_[tipe-item]_{rarity}_{name}_{sisa-primogems}` kedalam file dengan path berdasarkan variable `cur_dir`

Penamaan path untuk folder dan file terdapat pada `int main()` yang nantinya akan dipassing kedalam fungsi `gacha()`. <br>
Untuk kode penamaan folder/file adalah sebagai berikut.
```c
while (1)
{
    // create dir name
    char cur_dir[100], num_dir[5];
    strcpy(cur_dir, "gacha_gacha/");
    int round_nine = total_gacha - (total_gacha % 90);
    sprintf(num_dir, "%d", round_nine);
    strcat(cur_dir, "tot_gacha");
    strcat(cur_dir, num_dir);
    strcat(cur_dir, "/");
    create_dir(cur_dir);

    for (int j = 0; j < 9; j++)
    {
        // create filename
        time_t timer;
        char formatted_time[100], number[5];
        char temp_dir[100];
        strcpy(temp_dir, cur_dir);
        struct tm *tm_info;
        timer = time(NULL);
        tm_info = localtime(&timer);
        strftime(formatted_time, 100, "%H:%M:%S", tm_info);
        int round_to_10 = total_gacha - (total_gacha % 10);
        sprintf(number, "%d", round_to_10);

        strcat(temp_dir, formatted_time);
        strcat(temp_dir, "_gacha_");
        strcat(temp_dir, number);
        strcat(temp_dir, ".txt");

        // ...
    }
}
```
Sesuai letak comment, blok kode penamaan folder/file terletak di bawah comment tersebut.

### 1e

Proses untuk melakukan gacha item akan dimulai bertepatan dengan anniversary pertama kali mas Refadi bermain bengshin impek, yaitu pada 30 Maret jam 04:44.  Kemudian agar hasil gacha nya tidak dilihat oleh teman kos nya, maka 3 jam setelah anniversary tersebut semua isi di folder gacha_gacha akan di zip dengan nama not_safe_for_wibu dengan dipassword "satuduatiga", lalu semua folder akan di delete sehingga hanya menyisakan file (.zip)
 <br>
```c


...

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


```
Fungsi `wait_date()` adalah untuk membuat program menunggu hingga waktu yang ditentukan, yaitu `30 Maret jam 04:44`. <br>
Sedangkan cuplikan kode pada fungsi `cek_primo()` membuat program menunggu hingga 3 jam setelah program dimulai.

Pada akhir program, semua folder dan file dalam folder `gacha_gacha/` akan di-zip dan dipassword sesuai ketentuan soal. <br>
Untuk kode zip adalah sebagai berikut.
```c
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

```


### Kendala Soal 1
Sudah dibuat beberapa fungsi sesuai dengan permintaan namun tidak dapat berjalan sesuai yang d harapkan.
### Screenshot Soal 1
- Compile <br>
![Screenshoot_1_Compile](/uploads/e863f2bb34b89eba5d16a01e7a5f93df/Screenshoot_1_Compile.png)    
<br>

- Hasil Program <br>
![Screenshoot_1_Hasil_Gacha](/uploads/0895100f7bafe475542434823e551768/Screenshoot_1_Hasil_Gacha.png)    
<br>

## Jawaban Soal 2 
## Soal 2
Japrun bekerja di sebuah perusahaan dibidang review industri perfilman, dia mendapatkan sebuah proyek   
untuk mencari drama korea yang tayang dan sedang ramai di Layanan Streaming Film untuk diberi review.
Japrun sudah mendapatkan beberapa foto-foto poster serial dalam bentuk zip untuk diberikan review, 
tetapi didalam zip tersebut banyak sekali poster drama korea dan dia harus memisahkan
poster-poster drama korea tersebut tergantung dengan kategorinya. Japrun merasa kesulitan untuk 
melakukan pekerjaannya secara manual, kamu sebagai programmer diminta Japrun untuk menyelesaikan pekerjaannya.

### 2A
**Deskripsi Soal**  
Pada soal ini kita diminta untuk mengextract zip dan menghapus folder yang tidak dibutuhkan.

**Kode Program**
```
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
 
```

**Penjelasan**  
Menganalisasi variable child_id dengan tipe data pid_t dengan memanggil function fork()
lalu membuat folder dengan argument {"mkdir", "-p", "/home/argadewanata/shift2/drakor",NULL}
untuk menjalankan command execv
selanjutnya mengunzip folder dengan argument {"unzip","drakor.zip","-d","/home/argadewanata/shift2/drakor/",NULL}
lalu menghapus file yang tidak diperlukan dengan argument {"rm", "-rf", "/home/noob/shift2/drakor/coding", "/home/noob/shift2/drakor/trash", "/home/noob/shift2/drakor/song", NULL}

### 2B  
**Deskripsi Soal**  
Pada soal ini kita diminta untuk membuat folder untuk setiap jenis file yang ada di dalam zip sesuai isi kategorinya.

**Kode Program**
```
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
```

**Penjelasan**  
Pada soal ini membuat folder untuk semua jenis kategori file di dalam zip dengan argument {"mkdir", "-p", folder_thriller,NULL}

### 2C
**Deskripsi Soal**  
Setelah folder kategori berhasil dibuat, program akan memindahkan poster ke folder
dengan kategori yang sesuai dan di rename dengan nama sesuai kategori.

**Kode Program**
```
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
```

**Penjelasan**  
Pada soal ini memindahkan poster ke folder dengan kategori yang sesuai dengan nama yang telah di ubah sesuai kategorinya dengan menggunakan argument {"find", default_path, "-type", "f", "-iname", "*thriller*", "-exec", "mv", "{}", folder_thriller, ";", NULL}

### Kendala Soal 2    
Pada nomor 2C hasil solusi kami lakukan tidak selalu memindahkan file kedalam folder thriller, untuk nomor 2D dan 2E kami belum menemukan solusinya

### Screenshot Soal 2  
![Screenshot_soal_2.1](/uploads/c7b0f0f5f637423a3693576721655df6/Screenshot_soal_2.1.jpg)  

![Screenshot_soal_2.2](/uploads/253bb615a4cdffc57d4d9274d1961994/Screenshot_soal_2.2.jpg)  

## Jawaban Soal 3 

### Kendala Soal 3  
Pada nomor 2D, hasil solusi yang kami lakukan tidak selalu menghapus seluruh file yang terdapat "bird" pada nama filenya.Terkadang mampu menghapus seluruhnya, menghapus sebagian, atau tidak menghapus file "bird" sama sekali.  

### Screenshot Soal 3
Hasil akhir di directory /home/[USER]/modul2/darat   
![Screenshot_Soal3_i](/uploads/06d37d35bb50133eb3ee518870a86dc9/Screenshot_Soal3_i.jpeg)    

Hasil akhir di directory /home/[USER]/modul2/air  
![Screenshot_Soal3_ii](/uploads/2f6924caec820aab0d710d8c81dc6641/Screenshot_Soal3_ii.jpeg)       

Hasil akhir di file list.txt pada directory pada directory /home/[USER]/modul2/air/list.txt  
![Screenshot_Soal3_iii](/uploads/0e79c4d981a9388e543faa6691f3b6bc/Screenshot_Soal3_iii.jpeg)  

### 3A  
**Deksripsi Soal**  
Membuat directory "/home/[USER]/modul2/darat" lalu 3 detik kemudian membuat directory "/home/[USER]/modul2/air"    

**Kode Program**
```
    pid_t child_createdir_darat;
    pid_t child_createdir_air;
    pid_t child_move_air;
    pid_t child_remove;
    pid_t child_unzip;

    int status;

    /*
        Nomor 3A :  
        Membuat dir  "/home/[USER]/modul2/darat???  lalu 3 detik kemudian  membuat  dir  "home/[USER]/modul2/air???
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
```  

**Penjelasan**  
Melakukan spawn process child_createdir_darat untuk membuat directory "/home/argadewanata/modul2/darat" dengan menggunakan execv perintah mkdir. Setelah 3 detik kemudian, melakukan spawn process child_createdir_air untuk membuat directory "/home/argadewanata/modul2/air" dengan menggunakan execv perintah mkdir. Digunakan sleep(3) agar proses dilakukan 3 detik kemudian.  

### 3B  
**Deskripsi Soal**  
Melakukan extract animal.zip ke directory ???/home/[USER]/modul2/???  

**Kode Program**  
```
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
```  

**Penjelasan**  
Melakukan spawn process child_unzip untuk melakukan unzip animal.zip ke dalam "/home/argadewanata/modul2/" dengan menggunakan execv dengan perintah unzip.  

### 3C
**Deskripsi Soal**  
Hasil extract yang telah didapat dari soal 3B dimasukkan sesuai dengan namanya pada folder yang telah dibuat pada soal 3A. Apabila terdapat hewan yang tidak memiliki keterangan air atau darat akan dihapus.  

**Kode Program**
```
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
```  

**Penjelasan**    
Melakukan pembacaan directory "/home/argadewanata/modul2/animal".   
Kemungkinan 1 :   
Jika terdapat kata "darat" pada nama file-nya maka akan dilakukan spawn process child_move_darat untuk melakukan pemindahan file tersebut ke directory "/home/argadewanata/modul2/darat" dengan memanfaatkan execv perintah mv.     
Kemungkinan 2 :  
Jika terdapat kata "air" pada nama file-nya maka akan dilakukan spawn process child_move_air untuk melakukan pemindahan file tersebut ke directory "/home/argadewanata/modul2/air" dengan memanfaatkan execv perintah mv.  
Kemungkinan 3 :  
Jika terdapat file yang tidak memiliki kata "air" ataupun "darat" pada nama file-nya maka akan dihapus menggunakan exec perintah rm.  

### 3D  
**Deskripsi Soal**  
Menghapus file yang terdapat kata "bird" pada nama file-nya di dalam directory "/home/argadewanata/modul2/darat"  

**Kode Program**    
```
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
```  

**Penjelasan**   
Melakukan spawn process child_remove_bird untuk melakukan penghapusan file yang terdapat kata "bird" pada nama file-nya. Untuk melakukan hal tersebut, digunakan execl dengan perintah rm -f/home/argadewanata/modul2/darat/*bird* agar mampu melakukan force remove pada file yang terdapat pola kata "bird" di directory "/home/argadewanata/modul2/darat"  

### 3E          
**Deskripsi Soal**        
Membuat  list .txt yang berisi list nama hewan dengan format UID_[UID file permission]_Nama File.[jpg/png] pada directory "/home/argadewanata/modul2/air"    

**Kode Program**          
```
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
```

**Penjelasan**        
Melakukan pembacaan pada directory "/home/argadewanata/modul2/air/" dengan perintah opendir dan pembukaan file list.txt dengan perintah fopen. Setelah list.txt dapat terbuka, digunakan while loop selama masih ada pembacaan directory "/home/argadewanata/modul2/air/". Selama while loop berlangsung, UserID didapatkan dengan perintah cuserid, file permission didapatkan dengan fungsi - fungsi pada library #include <sys/stat.h>, nama file didapatkan dengan perintah ep2->d_name. Seluruh hal tersebut kemudian dituliskan ke dalam list.txt dengan perintah sprintf.  




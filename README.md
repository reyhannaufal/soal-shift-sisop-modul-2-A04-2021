# Laporan Soal Shift Modul 2

### Kelompok A04
- Ihsannur Rahman Qalbi 05111940000090
- Muhamad Fikri Sunandar 05111940000135
- Reyhan Naufal Rahman 05111940000171
### Daftar isi
1. [NO 1](#NO1)
2. [NO 2](#NO2)
3. [NO 3](#NO3)

## NO1
Soal nomor 1 membutuhkan konsep daemon dan konsep execv yang berjalan baik di dalam konsep fork. Maka no 1 membuat fungsi make_daemon untuk membuat daemon dan fungsi fork_f untuk mengeksekusi execv di dalam konsep fork.
```sh
void make_daemon(pid_t *pid, pid_t *sid, char *dirPath)
{
    *pid = fork();
 
    if (*pid < 0) {
        exit(EXIT_FAILURE);
    }
 
    if (*pid > 0) {
        exit(EXIT_SUCCESS);
    }
 
    umask(0);
 
    *sid = setsid();
    if (*sid < 0) {
        exit(EXIT_FAILURE);
    }
 
    if ((chdir(dirPath)) < 0) {
        exit(EXIT_FAILURE);
    }
 
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
}
}
```
Fungsi make_daemon memiliki parameter pid untuk menyimpan id, sid untuk menyimpan session, dan dirPath untuk menyimpan path yang akan menjadi root path dari fungsi daemon.
```sh
void fork_f(char *comm, char *argv[]){
 
    pid_t child_id;
    int status;
    
    child_id = fork();
    

    if (child_id < 0) {
        exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
    }

    if (child_id == 0) {
        // this is child
        execv(comm, argv);
    } else {
        // this is parent
        while ((wait(&status)) > 0);
        return;
    }
    return;
}
```
Fungsi fork_f berisi parameter comm untuk menyimpan command apa yang akan dijalankan, dan argv[] untuk menyimpan argumen yang akan dijalankan oleh comm. Selanjutnya setelah membuat daemon dengan fungsi daemon di dalam while(1) diisi algoritma untuk menyelesaikan soal no 1. 
### 1a
Steven ingin membuat Musyik untuk mp3, Fylm untuk mp4, dan Pyoto untuk jpg maka dibuatlah fungsi make_folder
```sh
void make_folder() {

    char *argv[] = {"mkdir", "Pyoto", "Musyik", "Fylm", NULL};
    fork_f("/bin/mkdir", argv);

    return;
}
```
Fungsi tersebut berisi cmmand mkdir dan nama folder yang akan dibuat. Lalu memanggil fungsi_fork yang akan mengeksekusi program dan membuat folder yang diinginkan.
### 1b
Serta Steven akan mendownload musik, film, dan foto dari link yang disediakan. 
```sh
void download_zip() {

    char *argv[] = {"wget", "-q", "--no-check-certificate", "https://drive.google.com/u/0/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download", "-O", "Foto_for_Stevany.zip", NULL};
    fork_f("/bin/wget", argv);
    
    char *argv2[] = {"wget", "-q", "--no-check-certificate", "https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download", "-O", "Musik_for_Stevany.zip", NULL};
    fork_f("/bin/wget", argv2);
    
    char *argv3[] = {"wget", "-q", "--no-check-certificate", "https://drive.google.com/u/0/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download", "-O", "Film_for_Stevany.zip", NULL};
    fork_f("/bin/wget", argv3);
    
    return;
}
```
Maka dibuat fungsi download_zip yang berisi argv link dan command yang sesuai dengan kebutuhan. 
### 1c
Steven tidak ingin filenya bertipe zip sehingga perlu mengekstraknya. 
```sh
void extract_zip(char *dirPath) {

    char tmp[500];
    strcpy(tmp, dirPath);
    strcat(tmp, "Foto_for_Stevany.zip");

    char *argv[] = {"unzip", tmp, "-d", dirPath, NULL};
    fork_f("/bin/unzip", argv);

    strcpy(tmp, dirPath);
    strcat(tmp, "Musik_for_Stevany.zip");

    char *argv2[] = {"unzip", tmp, "-d", dirPath, NULL};
    fork_f("/bin/unzip", argv2);

    strcpy(tmp, dirPath);
    strcat(tmp, "Film_for_Stevany.zip");

    char *argv3[] = {"unzip", tmp, "-d", dirPath, NULL};
    fork_f("/bin/unzip", argv3);   
    
    return;
}
```
Penjelasannya
Membuat fungsi extract_zip yang memiliki parameter dirPath untuk mempassing path yang akan melakukan proses unzip. Di dalam fungsi extract_zip terdapat variabel argv untuk menyimpan command unzip dan nama file zip yang akan diunzip. Selanjutnya memanggil fungsi fork_f untuk menjalankan command yang telah dibuat tadi. 
### 1d
Program memindahkan file yang telah diextrak ke folder yang telah dibuat tadi.
```sh
void move_file(char *dirPath, char *destPath) {

    DIR *d;
    struct dirent *dir;
    d = opendir(dirPath);

    while ((dir = readdir(d)) != NULL)
    {
        char tmp[500];
        strcpy(tmp, dirPath);
        strcat(tmp, dir->d_name);

        char *argv[] = {"mv", tmp, destPath, NULL};
        fork_f("/bin/mv", argv);
    }

    closedir(d);

    return;
}
```
Membuat fungsi move_file yang memiliki 2 parameter yakni dirPath untuk menyimpan path folder yang berisi semua file yang akan dipindahkan berada dan destPath yang berisi path yang akan dijadikan destinasi file tadi. Di dalam fungsi tersebut berisi algoritma untuk membua sebuah folder (dgn path yang disimpan di dirPath) dan membaca semua file di dalam folder tersebut lalu memindahkannya dengan command mv dan fungsi fork_f. 
### 1e
Stevan ingin program dari 1.a-1.d dijalankan 6 jam sebelum waktu ulang tahun si Stevany. 
```sh
    int b_ultah = 58920; //jam 16:22 menit
    ...
    ...
       if ((now_s >= b_ultah) && (flag1 == 1)) {
                  flag1 = 0;
                  make_folder();
                  download_zip();
                  extract_zip(dirPath);
                  move_file("/home/mufis/PS/Pratikum_02/soal1/FOTO/", "/home/mufis/PS/Pratikum_02/soal1/Pyoto/");
                  move_file("/home/mufis/PS/Pratikum_02/soal1/MUSIK/", "/home/mufis/PS/Pratikum_02/soal1/Musyik/");
                  move_file("/home/mufis/PS/Pratikum_02/soal1/FILM/", "/home/mufis/PS/Pratikum_02/soal1/Fylm/");
        }
```
Di dalam main membuat variabel integer yang berisi angka 58920 yang jika dikonversi ke waktu jam dan menit menjadi 16 jam 22 menit (waktu 6 jam sebelum ulang tahun). Variabel ini akan digunakan untuk pengkondisian pada nantinya program dijalankan, jika waktu yang diset telah terlewati atau sama maka program berjalan. 
### 1f
Stevan ingin ketika waktu ulang tahun si Stevany maka program akan menzip semua folder. 
```sh
    int ultah = 80520; //jam 22:22 menit
```
Maka dibuat variabel lagi di main untuk menyimpan angka 80520 yang jika dikonversi akan menjadi jam yang sesuai dengan ulang tahun Stevany. 
```sh
    if ((now_s >= ultah) && (flag2 == 1)) {
                flag2 = 0;
                zip_folder();
                delete_folder();
    }
```
Di dalam pengkondisian ulang tahun dengan variabel tadi dibuat memanggil dua fungsi yakni zip_folder dan delete_folder. Fungsi zip_folder berfungsi untuk menzip semua folder yang ada, sedangkan delete_folder untuk menghapus semua folder yang ada. 
```sh
void zip_folder() {

    char *argv[] = {"zip", "-r", "Lopyu_Stevany.zip", "Pyoto", "Musyik", "Fylm", "FOTO", "MUSIK", "FILM", NULL};
    fork_f("/bin/zip", argv);
 
    return;
}

void delete_folder() {

    char *argv[] = {"rm", "-r", "Pyoto", "Musyik", "Fylm", "FOTO", "MUSIK", "FILM", NULL};
    fork_f("/bin/rm", argv);
 
    return;
}
```
Di dalam fungsi zip_folder berisi argv untuk menyimpan command zip dan nama file untuk menyimpan zip serta folder-folder yang akan dizip. Sedangkan, pada folder delete_folder disimpan fungsi command rm untuk menghapus semua folder yang ada. 

## NO3
Pengerjaan soal nomor 3 menggunakan template untuk process menjadi daemon process dan fork
```sh
	char s[PATH_MAX];
	getcwd(s,sizeof(s));
	
	pid_t pid,sid;
	pid = fork();
	
	if(pid <0){
		exit(EXIT_FAILURE);
	}
	if(pid > 0){
		exit(EXIT_SUCCESS);
	}
	umask(0);
	sid = setsid();
	if(sid < 0){
		exit(EXIT_FAILURE);
	}
	if((chdir(s))<0){
		printf("\nbar\n");
		exit(EXIT_FAILURE);
	}
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
```
Yang berbeda dari modul adalah bagian chdir, dimana working directory dirubah menjadi directory dimana program dipanggil.

```sh
void fork_(char *cmd, char *arg[])
{
	pid_t id;
	int status;
	id = fork();
	if(id<0)
	{
		exit(EXIT_FAILURE);
	}
	if(id==0)
	{
		execv(cmd,arg);
	}
}
```
Untuk fungso forrk_ dihilangkan bagian wait, untuk menghindari penamaan file/folder yang tidak sesuai dengan pola waktu

### 3a
```sh
	while(1){
		printf("foo");
		make();
		sleep(40);
	}
	return 0;
```
Selama program daemon berjalan akan terus memanggil fungsi make() dengan delay 40 second.
```sh
void make(){
	time_t waktu;
	time(&waktu);
	pid_t id;
	int status;
	id =fork();
	if (id<0){
		exit(EXIT_FAILURE);
	}
	if (id==0){
		placeholdir(waktu);
		char* sk[]={"echo","-n",NULL};
		execv("/bin/echo", sk);
	}
}
```
 Fungsi make() adalah fungsi yang me-fork fungsi yang akan membuat folder (disini dinamakan placeholdir(time_t t)dengan parameter waktu saat fungsi make() dipanggil
 ```sh
 void placeholdir(time_t waktu){
	char* date;
	struct tm tim = *localtime(&waktu);
	asprintf(&date,"%d-%02d-%02d_%02d:%02d:%02d" , tim.tm_year +1900, tim.tm_mon +1, tim.tm_mday, tim.tm_hour, tim.tm_min, tim.tm_sec);
	char *arg[]={"mkdir",date,NULL};
	fork_("/bin/mkdir",arg);
   int i;
	for(i=0;i<10;i++){
	download(date);
	sleep(5);
	}
	text(date);
	zipfolder(date);
	sleep(5);
	removefolder(date);
}
 ```
 Di fungsi placeholdir waktu yang dipassing akan dirubah menjadi format nama fodler seperti permintaan soal kemudian melakukan execv mkdir

### 3b
Untuk mendownload file, di fungsi placeholdir dijalankan looping for dengan delay 5 detik  di setiap akhir loop
```sh
for(i=0;i<10;i++){
	download(date);
	sleep(5);
	}
```
fungsi download menggunakan parameter date yang merupakan string nama direktori yang dibuat.
```sh
void download (char *tang){
	printf("\nFOOBAR1\n");
	time_t waktu;
	time(&waktu);
	char* date;
	char* pix;
	char* date2;
	struct tm tim = *localtime(&waktu);
	asprintf(&pix,"https://picsum.photos/%li" ,waktu%1000+50);
	asprintf(&date,"%d-%02d-%02d_%02d:%02d:%02d" , tim.tm_year +1900, tim.tm_mon +1, tim.tm_mday, tim.tm_hour, tim.tm_min, tim.tm_sec);
	asprintf(&date2,"%s/%s.jpeg", tang,date);
	char *arg[]={"wget","--no-check-certificate","-O",date2,"-b","-q","-c",pix,NULL};
	fork_("/usr/bin/wget",arg);
}
```
string pix dan date2 masing masing adalah string alamat download file dan string hasil concate dari nama direktori yang dibuat dengan string penamaan file yang dijadikan direktori download file
### 3c
setelah looping download file selesai akan memanggil fungsi text yang akan membuat file text
```sh
void text(char* path){

	FILE *tex;
	char *namafile;
	asprintf(&namafile,"%s/status.txt",path);
	char* msg;
	asprintf(&msg,"Download Success");
	tex = fopen(namafile, "w");
	caesar5(msg);
	fputs(msg,tex);
	fclose(tex);
}

```
Text akan berisi string "Download Success" yang sudah di cipher melalui fungsi caesar5
```sh
void caesar5(char* succ){
	int i=0;
	while (succ[i] != NULL){
		if (((succ[i] >= 'a') && (succ[i]<= 'z'-5))||((succ[i] >= 'A')&&(succ[i]<= 'z'-5))){
			succ[i] =succ[i] + 5;
		}
		else if (((succ[i] <= 'z') && (succ[i] > 'z'-5))||((succ[i] <= 'Z')&&(succ[i]> 'z'-5))){
			succ[i] = succ[i] - 21;
		}
		i++;
	}
}
```
Kemudia akan direktori akan di zip dengan zipfolder
```sh
	zipfolder(date);
	sleep(5);
	removefolder(date);
------------------------------
void zipfolder(char *tang){
	char* zipname;
	asprintf(&zipname,"%s.zip",tang);
	char* arg[] = {"zip","-r",zipname,tang,NULL};
	fork_("/usr/bin/zip",arg);
	
}
```
Dan direktori akan di delete setelah delay 5 detik untuk menghindari file di delete sebelum proses zip selesai
```sh
void removefolder(char *tang){
	char* arg[]={"rm","-rf",tang,NULL};
	fork_("/bin/rm",arg);
}
```
### 3d dan 3e
Program tidak akan berjalan jika tidak menggunakan argumen yang sesuai (-x atau -z)
```sh
	if(argc !=2){
		printf("invalid # arg\n");
		exit(0);
	}
	if(!((argv[1][1]=='x')||(argv[1][1]=='X')||(argv[1][1]=='z')||(argv[1][1]=='Z'))){
		printf("\ninvalid arg = %c\n",argv[1][1]);
		exit(0);
```

Sebelum loop daemon dijalankan, program akan membuat killer
```sh
killer(argv[1][1],(int)getpid(),argv[0]);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	while(1){
		printf("foo");
		make();
		sleep(40);
	}
```
fungsi killer menggunakan parameter argv[1][1] yaitu argumen (x/z), pid, dan nama program
```sh
void killer(char *c,int pid,char* ch){
	FILE *tex;
	char* script;
	tex = fopen("Killer.sh", "w");
	if((c=='x') || (c =='X')){
		asprintf(&script,"\#!/bin/bash\nkill -9 %d\nrm -- \"$0\"",pid);
		fputs(script,tex);
		fclose(tex);
	}
	if((c=='z') || (c =='Z')){
		asprintf(&script,"\#!/bin/bash\nkillall -9 %s\nrm -- \"$0\"",ch);
		fputs(script,tex);
		fclose(tex);
	}
}
```
Ketika arg -x digunakan, killer akan menggunakan script kill pid untuk kill process utama sehingga proses download, zip, dan delete tidak terhenti,
Ketika arg -z digunakan, killer akan menggunakan script killall namaprogram untuk kill semua process yang di spawn onleh program.

### Referensi yang digunakan dalam pengerjaan soal
https://www.alphr.com/echo-without-newline/

https://man7.org/linux/man-pages/man3/asprintf.3.html

https://stackoverflow.com/questions/1442116/how-to-get-the-date-and-time-values-in-a-c-program

https://stackoverflow.com/questions/22124413/how-to-use-wget-command-using-exec-command-in-linux

https://codeforwin.org/2018/01/c-program-create-file-write-contents.html

https://stackoverflow.com/questions/16678487/wget-command-to-download-a-file-and-save-as-a-different-filename

https://www.systutorials.com/in-linux-how-to-kill-a-process-and-all-its-child-processes/

https://stackoverflow.com/questions/11074401/command-line-argument-to-run-a-c-program

https://www.cyberciti.biz/tips/howto-run-wget-in-background.html

https://www.tutorialspoint.com/cprogramming/c_command_line_arguments.htm

https://stackoverflow.com/questions/8981164/self-deleting-shell-script



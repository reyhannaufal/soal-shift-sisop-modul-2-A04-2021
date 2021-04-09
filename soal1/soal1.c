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
#include <wait.h>
#include <dirent.h>
#include <unistd.h>

void fork_f(char *comm, char *argv[]);
void download_zip();
void make_folder();
void move_file();
void extract_zip(char *dirPath);
void delete_zip();
void zip_folder();
void delete_folder();
void make_daemon(pid_t *pid, pid_t *sid, char *dirPath);


int main()
{
    char *dirPath = "/home/mufis/PS/Pratikum_02/soal1/";
    pid_t pid, sid;
    make_daemon(&pid, &sid, dirPath);
    
    int b_ultah = 58920; //jam 16:22 menit
    int b_ultahl = 59040; // jam 16:24 (buat limit ajah)
    int ultah = 80520; //jam 22:22 menit
    int flag1 = 1, flag2 = 1;

    while(1) {
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        int now_s = tm.tm_hour*3600 + tm.tm_min*60 + tm.tm_sec;

        if((tm.tm_mon + 1 == 4) && (tm.tm_mday == 9)) {

            if (now_s >= b_ultahl) {
                flag1 = 0;
            }

            if ((now_s >= b_ultah) && (flag1 == 1)) {
                flag1 = 0;
                make_folder();
                download_zip();
                extract_zip(dirPath);
                move_file("/home/mufis/PS/Pratikum_02/soal1/FOTO/", "/home/mufis/PS/Pratikum_02/soal1/Pyoto/");
                move_file("/home/mufis/PS/Pratikum_02/soal1/MUSIK/", "/home/mufis/PS/Pratikum_02/soal1/Musyik/");
                move_file("/home/mufis/PS/Pratikum_02/soal1/FILM/", "/home/mufis/PS/Pratikum_02/soal1/Fylm/");
            }

            if ((now_s >= ultah) && (flag2 == 1)) {
                flag2 = 0;
                zip_folder();
                delete_folder();
            }
        }
        sleep(2);
    }

    return 0;
}

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

void make_folder() {

    char *argv[] = {"mkdir", "Pyoto", "Musyik", "Fylm", NULL};
    fork_f("/bin/mkdir", argv);

    return;
}

void download_zip() {

    char *argv[] = {"wget", "-q", "--no-check-certificate", "https://drive.google.com/u/0/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download", "-O", "Foto_for_Stevany.zip", NULL};
    fork_f("/bin/wget", argv);
    
    char *argv2[] = {"wget", "-q", "--no-check-certificate", "https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download", "-O", "Musik_for_Stevany.zip", NULL};
    fork_f("/bin/wget", argv2);
    
    char *argv3[] = {"wget", "-q", "--no-check-certificate", "https://drive.google.com/u/0/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download", "-O", "Film_for_Stevany.zip", NULL};
    fork_f("/bin/wget", argv3);
    
    return;
}

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
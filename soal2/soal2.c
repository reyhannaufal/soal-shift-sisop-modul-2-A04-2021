#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void fork_f(char *comm, char *argv[]);

int main()
{
    char *argv[] = {"unzip", "/home/ec2-user/soal-shift-sisop-modul-2-A04-2021/soal2/pets.zip", "-d", "/home/ec2-user/modul2/petshop", NULL};
    fork_f("/usr/bin/unzip", argv);

    chdir("/home/ec2-user/modul2/petshop");

    char *argv2[] = {"rm", "-r", "apex_cheats", "musics", "unimportant_files", NULL};
    fork_f("/usr/bin/rm", argv2);

    char *argv3[] = {"mkdir", "betta", "cat", "chicken", "dog", "frog", "guinea", "otter", "hamster", "iguana", "ilama", "parrot", "rabbit", "racoon", "sheep", "tiger", NULL};
    fork_f("/usr/bin/mkdir", argv3);

    DIR *d;
    struct dirent *dir;
    d = opendir("/home/ec2-user/modul2/petshop");

    while ((dir = readdir(d)) != NULL)
    {
        if (strstr(dir->d_name, "betta;"))
        {
            //algo here
            /*
               1. 
            */

            char *argv[] = {"mv", dir->d_name, "betta", NULL};
            fork_f("/usr/bin/mv", argv);
            //and text here
        }

        if (strstr(dir->d_name, "cat;"))
        {

            char *argv[] = {"mv", dir->d_name, "cat", NULL};

            fork_f("/usr/bin/mv", argv);
        }
        if (strstr(dir->d_name, "chicken;"))
        {
            char *argv[] = {"mv", dir->d_name, "chicken", NULL};
            fork_f("/usr/bin/mv", argv);
        }
        if (strstr(dir->d_name, "dog;"))
        {
            char *argv[] = {"mv", dir->d_name, "dog", NULL};
            fork_f("/usr/bin/mv", argv);
        }
        if (strstr(dir->d_name, "frog;"))
        {
            char *argv[] = {"mv", dir->d_name, "frog", NULL};
            fork_f("/usr/bin/mv", argv);
        }
        if (strstr(dir->d_name, "guinea pig;"))
        {
            char *argv[] = {"mv", dir->d_name, "guinea", NULL};
            fork_f("/usr/bin/mv", argv);
        }
        if (strstr(dir->d_name, "hamster;"))
        {
            char *argv[] = {"mv", dir->d_name, "hamster", NULL};
            fork_f("/usr/bin/mv", argv);
        }
        if (strstr(dir->d_name, "iguana;"))
        {
            char *argv[] = {"mv", dir->d_name, "iguana", NULL};
            fork_f("/usr/bin/mv", argv);
        }
        if (strstr(dir->d_name, "ilama;"))
        {
            char *argv[] = {"mv", dir->d_name, "ilama", NULL};
            fork_f("/usr/bin/mv", argv);
        }
        if (strstr(dir->d_name, "otter;"))
        {
            char *argv[] = {"mv", dir->d_name, "otter", NULL};
            fork_f("/usr/bin/mv", argv);
        }
        if (strstr(dir->d_name, "parrot;"))
        {
            char *argv[] = {"mv", dir->d_name, "parrot", NULL};
            fork_f("/usr/bin/mv", argv);
        }
        if (strstr(dir->d_name, "rabbit;"))
        {
            char *argv[] = {"mv", dir->d_name, "rabbit", NULL};
            fork_f("/usr/bin/mv", argv);
        }
        if (strstr(dir->d_name, "racoon;"))
        {
            char *argv[] = {"mv", dir->d_name, "racoon", NULL};
            fork_f("/usr/bin/mv", argv);
        }
        if (strstr(dir->d_name, "sheep;"))
        {
            char *argv[] = {"mv", dir->d_name, "sheep", NULL};
            fork_f("/usr/bin/mv", argv);
        }
        if (strstr(dir->d_name, "tiger;"))
        {
            char *argv[] = {"mv", dir->d_name, "tiger", NULL};
            fork_f("/usr/bin/mv", argv);
        }
    }

    return 0;
}

void fork_f(char *comm, char *argv[])
{

    pid_t child_id;
    int status;

    child_id = fork();

    if (child_id < 0)
    {
        exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
    }

    if (child_id == 0)
    {
        // this is child
        execv(comm, argv);
    }
    else
    {
        // this is parent
        while ((wait(&status)) > 0)
            ;
    }
    return;
}

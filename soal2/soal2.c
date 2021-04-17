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
char *str_toDir(char *ipt);
char *animalName(char *str);
char *renameAnimal(char *str, char *folder)
{
    char *name = animalName(str);
    char *ptr;
    while (ptr = strtok_r(name, "_", &name))
    {

        char *ptr2;
        int j = 0;

        char jenis[20], name[20], umur[10];
        char *temp = ptr;

        while (ptr2 = strtok_r(temp, ";", &temp))
        {
            if (j == 0)
            {
                strcpy(jenis, ptr2);
            }

            if (j == 1)
            {
                strcpy(name, ptr2);
            }

            if (j == 2)
            {
                strcpy(umur, ptr2);
            }

            j++;
        }

        char *argv[] = {"mv", str, name, NULL};
        fork_f("/usr/bin/mv", argv);

        char *argv2[] = {"mv", name, folder, NULL};
        fork_f("/usr/bin/mv", argv2);
    }
}

int main()
{
    char *argv[] = {"unzip", "/home/ec2-user/soal-shift-sisop-modul-2-A04-2021/soal2/pets.zip", "-d", "/home/ec2-user/modul2/petshop", NULL};
    fork_f("/usr/bin/unzip", argv);

    chdir("/home/ec2-user/modul2/petshop");

    char *argv2[] = {"rm", "-r", "apex_cheats", "musics", "unimportant_files", NULL};
    fork_f("/usr/bin/rm", argv2);

    char *argv3[] = {"mkdir", "betta", "cat", "chicken", "dog", "frog", "guinea pig", "otter", "hamster", "iguana", "ilama", "parrot", "rabbit", "racoon", "sheep", "tiger", NULL};
    fork_f("/usr/bin/mkdir", argv3);

    DIR *d;
    struct dirent *dir;
    d = opendir("/home/ec2-user/modul2/petshop");

    while ((dir = readdir(d)) != NULL)
    {
        if (strstr(dir->d_name, "betta;"))
        {
            renameAnimal(dir->d_name, "betta");
        }

        if (strstr(dir->d_name, "cat;"))
        {
            renameAnimal(dir->d_name, "cat");
        }
        if (strstr(dir->d_name, "chicken;"))
        {
            renameAnimal(dir->d_name, "chicken");
        }
        if (strstr(dir->d_name, "dog;"))
        {
            renameAnimal(dir->d_name, "dog");
        }
        if (strstr(dir->d_name, "frog;"))
        {
            renameAnimal(dir->d_name, "frog");
        }
        if (strstr(dir->d_name, "guinea pig;"))
        {
            renameAnimal(dir->d_name, "guinea pig");
        }
        if (strstr(dir->d_name, "hamster;"))
        {
            renameAnimal(dir->d_name, "hamster");
        }
        if (strstr(dir->d_name, "iguana;"))
        {

            renameAnimal(dir->d_name, "iguana");
        }
        if (strstr(dir->d_name, "ilama;"))
        {

            renameAnimal(dir->d_name, "ilama");
        }
        if (strstr(dir->d_name, "otter;"))
        {

            renameAnimal(dir->d_name, "otter");
        }
        if (strstr(dir->d_name, "parrot;"))
        {

            renameAnimal(dir->d_name, "parrot");
        }
        if (strstr(dir->d_name, "rabbit;"))
        {

            renameAnimal(dir->d_name, "rabbit");
        }
        if (strstr(dir->d_name, "racoon;"))
        {

            renameAnimal(dir->d_name, "racoon");
        }
        if (strstr(dir->d_name, "sheep;"))
        {

            renameAnimal(dir->d_name, "sheep");
        }
        if (strstr(dir->d_name, "tiger;"))
        {

            renameAnimal(dir->d_name, "tiger");
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

char *str_toDir(char *ipt)
{
    // printf("%s\n", ipt);

    int i = 0, tc = 0;
    char tmp[strlen(ipt)];
    while (1)
    {

        if (ipt[i] == ';')
        {
            tmp[tc] = '/';
        }
        else if (ipt[i] != ';')
        {
            tmp[tc] = ipt[i];
        }
        if (ipt[i] == '\0')
        {
            tmp[tc] = '\0';
            break;
        }
        i++;
        tc++;
    }
    return tmp;
}

char *animalName(char *str)
{
    int size;
    char *a;

    int i;
    for (i = 0; str[i] != '\0'; i++)
        ;

    size = i - 3;

    if (size < 1)
        return NULL;

    a = (char *)malloc(size * sizeof(char));

    for (i = 0; i < size - 1; i++)
    {
        a[i] = str[i];
    }
    a[i] = '\0';
    return a;
}

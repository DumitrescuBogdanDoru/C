/*
    Sa se scrie un program C care primeste ca si argument in
linie de comanda, calea catre un director.
Programul va verifica:
- numarul de argumente
- daca argumentul primit este director.
Programul va afisa la STDOUT numele tuturor intrarilor
din directorul respectiv.
    Task 1:
- sa se afiseze CALEA catre intrarile din director
    Task 2:
- sa se afiseze si TIPUL intrarilor din director
(Fisier/Director/Legatura --> lstat vs. stat)
    Task 3:
- sa se implementeze parcurgerea recursiva a directorului
(parcurgem recursiv subdirectoarele --> S_ISDIR(..) ....)
    Task 4:
- pentru fiecare legatura sa se afiseze continutul acestuia
(readlink)
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>
#include <dirent.h>

void parcurgere(DIR *dir, const char *path)
{
    struct stat *st = malloc(sizeof(struct stat));
    struct dirent *dt;
    char buffer[512];
    while ((dt = readdir(dir)) != NULL)
    {
        sprintf(buffer, "%s/%s", path, dt->d_name);
        lstat(buffer, st);
        if (S_ISDIR(st->st_mode))
        {
            printf("%s | DIRECTOR\n", buffer);
            if (strcmp(dt->d_name, ".") != 0 && strcmp(dt->d_name, "..") != 0)
            {
                DIR *mydir = opendir(buffer);
                parcurgere(mydir, buffer);
            }
        }
        if (S_ISREG(st->st_mode))
        {
            printf("%s | FISIER\n", buffer);
        }
        if (S_ISLNK(st->st_mode))
        {
            printf("%s | LEGATURA SIMBOLICA\n", buffer);
            char aux_buffer[512];
            ssize_t len = readlink(buffer, aux_buffer, sizeof(aux_buffer));
            if (len != -1)
            {
                aux_buffer[len] = '\0';
            }
            printf("---------------------------------------------------\n%s (CONTINUT):\n\n", aux_buffer);
            struct stat *st1 = malloc(sizeof(struct stat));
            lstat(aux_buffer, st1);
            if (S_ISREG(st1->st_mode))
            {
                int fd, a;
                char buff[30];
                fd = open(aux_buffer, O_RDONLY);
                do
                {
                    a = read(fd, buff, sizeof(buff));
                    for (int i = 0; i < a; i++)
                    {
                        printf("%c", buff[i]);
                    }
                } while (a > 0);
                printf("\n=====================\n");
            }
            if (S_ISDIR(st1->st_mode))
            {
                if (strcmp(dt->d_name, ".") != 0 && strcmp(dt->d_name, "..") != 0)
                {
                    DIR *mydir = opendir(aux_buffer);
                    parcurgere(mydir, aux_buffer);
                }
            }
        }
    }
    return;
}

int main(int argc, char const *argv[])
{
    DIR *dir;
    struct stat *st = malloc(sizeof(struct stat));
    if (argc != 2)
    {
        perror("eroare");
        exit(-1);
    }
    dir = opendir(argv[1]);
    if (stat(argv[1], st) == 0 && S_ISDIR(st->st_mode))
    {
        printf("Este director!\n");
    }
    else
    {
        perror("Nu este director!");
        exit(-2);
    }
    parcurgere(dir, argv[1]);
    return 0;
}

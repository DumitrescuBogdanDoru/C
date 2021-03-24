/*
    Sa se scrie un program C care primeste ca si argument
in linie de comanda calea catre un fisier.
- sa se verifice numarul de argumente
- sa se verifice daca arg este fisier
Programul va citi in intregime fisierul, in mod eficient,
si va afisa numarul de litere mici, litere mari si cifre.

    TASK BONUS: sa se afiseze permisiunile fisierului si
dimensiunea in octeti.
S_ISDIR, S_ISREG, S_ISLNK

    TASK BONUS 2: afisarea sa se faca intr-un fisier
(care nu exista inainte de rulare)
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>
#define BUFSIZE 256

int main(int argc, char *argv[])
{
    char *buff = (char *)malloc(BUFSIZE * sizeof(char));
    struct stat *buffer;
    int fd, fd1, a, countmici = 0, countmari = 0, countcifre = 0;
    if (argc != 2)
    {
        perror("eroare");
        exit(-1);
    }
    buffer = (struct stat *)malloc(sizeof(struct stat));
    fd = open(argv[1], O_RDONLY);
    if (stat(argv[1], buffer) == 0 && S_ISREG(buffer->st_mode))
    {
        printf("Este fisier!\n");
    }
    else
    {
        perror("Nu este fisier!");
        exit(-2);
    }
    do
    {
        a = read(fd, buff, 30);
        printf("%s", buff);
        for (int i = 0; i < a; i++)
        {
            if (buff[i] >= 'a' && buff[i] <= 'z')
                countmici++;
            if (buff[i] >= 'A' && buff[i] <= 'Z')
                countmari++;
            if (buff[i] >= '0' && buff[i] <= '9')
                countcifre++;
        }

    } while (a > 0);
    free(buff);

    printf("Numar litere mici %d\n", countmici);
    printf("Numar litere mari %d\n", countmari);
    printf("Numar cifre %d\n", countcifre);

    printf("Dimensiune: %ld bytes\n", buffer->st_size);
    printf("Permisiuni: ");
    printf((S_ISDIR(buffer->st_mode)) ? "d" : "-");
    printf((buffer->st_mode & S_IRUSR) ? "r" : "-");
    printf((buffer->st_mode & S_IWUSR) ? "w" : "-");
    printf((buffer->st_mode & S_IXUSR) ? "x" : "-");
    printf((buffer->st_mode & S_IRGRP) ? "r" : "-");
    printf((buffer->st_mode & S_IWGRP) ? "w" : "-");
    printf((buffer->st_mode & S_IXGRP) ? "x" : "-");
    printf((buffer->st_mode & S_IROTH) ? "r" : "-");
    printf((buffer->st_mode & S_IWOTH) ? "w" : "-");
    printf((buffer->st_mode & S_IXOTH) ? "x" : "-");
    printf("\n\n");

    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    char *filename = "/mnt/c/Users/ASUS/Desktop/an3/so/lab3/afisare.txt"; //cale catre fisierul unde vrei sa scrii informatiile
    fd1 = creat(filename, mode);

    sprintf(buff, "Dimensiune: %ld bytes\n", buffer->st_size);
    sprintf(buff + strlen(buff), "Numar litere mici:%d\nNumar litere mari:%d\nNumar cifre:%d\n", countmici, countmari, countcifre);
    sprintf(buff + strlen(buff), "%s", "Permisiuni: ");
    sprintf(buff + strlen(buff), "%s", (S_ISDIR(buffer->st_mode)) ? "d" : "-");
    sprintf(buff + strlen(buff), "%s", (buffer->st_mode & S_IRUSR) ? "r" : "-");
    sprintf(buff + strlen(buff), "%s", (buffer->st_mode & S_IWUSR) ? "w" : "-");
    sprintf(buff + strlen(buff), "%s", (buffer->st_mode & S_IXUSR) ? "x" : "-");
    sprintf(buff + strlen(buff), "%s", (buffer->st_mode & S_IRGRP) ? "r" : "-");
    sprintf(buff + strlen(buff), "%s", (buffer->st_mode & S_IWGRP) ? "w" : "-");
    sprintf(buff + strlen(buff), "%s", (buffer->st_mode & S_IXGRP) ? "x" : "-");
    sprintf(buff + strlen(buff), "%s", (buffer->st_mode & S_IROTH) ? "r" : "-");
    sprintf(buff + strlen(buff), "%s", (buffer->st_mode & S_IWOTH) ? "w" : "-");
    sprintf(buff + strlen(buff), "%s\n", (buffer->st_mode & S_IXOTH) ? "x" : "-");

    printf("BUFFER:\n%s", buff);

    write(fd1, buff, strlen(buff));
    close(fd);
    close(fd1);
    return 0;
}

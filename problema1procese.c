
/*
    Sa se scrie un program C format din 2 procese: 1 parinte si 1 copil.
Copilul va afisa mesajul: "Hello world" dupa care se va termina cu un cod de iesire ales de voi.
Parintele va prealua starea copilului si va afisa PIDul si codul de iesire.
    Change 1: 1 Parinte si 2 Copii (frati)
*/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>
#include <dirent.h>

int main(int argc, char const *argv[])
{
    int pid1 = fork();
    int status;
    if (pid1 == -1)
    {
        perror("EROARE");
        exit(1);
    }
    if (pid1 == 0)
    {
        printf("Hello world\n");
        exit(0);
    }
    int pid2 = fork();
    if (pid2 == -1)
    {
        exit(2);
    }
    if (pid2 == 0)
    {
        printf("Hello world 2\n");
        exit(99);
    }
    wait(&status);
    if (WIFEXITED(status))
    {
        printf("Status: %d\n", WEXITSTATUS(status));
    }
    wait(&status);
    if (WIFEXITED(status))
    {
        printf("Status: %d\n", WEXITSTATUS(status));
    }
    return 0;
}

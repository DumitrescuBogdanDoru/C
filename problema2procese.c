
/*
    Change 2: sa se modifice programul anterior astfel incat: pentru fiecare numar primit
ca si argument in linie de comanda, sa se creeze un proces nou copil care numara de la
1 pana la numarul primit.

EX: program 3 4 7
copil1: 1 2 3
copil2: 1 2 3 4
copil3: 1 2 3 4 5 6 7

    Change 3***: Programul se invoca: <program> <cale-fisier> n1 n2 n3 .....
Sa se adauge schimbarile necesare pentru a putea invoca ls -l pentru <cale-fisier>.
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
    int k = 2;
    pid_t status;
    while (k <= argc)
    {
        int pid = fork();
        if (pid == -1)
        {
            printf("EROARE LA COPCHIL");
            exit(1);
        }
        if (pid == 0)
        {
            for (int i = 1; i <= atoi(argv[k]); i++)
            {
                printf("%d ", i);
            }
            printf("\n");
            exit(k);
        }
        wait(&status);
        if (WIFEXITED(status))
        {
            printf("Status: %d\n", WEXITSTATUS(status));
        }
        k++;
    }
    int copie_parinte = fork();
    if (copie_parinte == -1)
    {
        printf("EROARE LA COPCHIL");
        exit(10);
    }
    if (copie_parinte == 0)
    {
        execlp("ls", "ls", "-l", argv[1], NULL);
        exit(1);
    }
    wait(&status);
    if (WIFEXITED(status))
    {
        printf("Status: %d\n", WEXITSTATUS(status));
    }
    return 0;
}

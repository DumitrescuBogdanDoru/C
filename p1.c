/*Problema 1:
Sa se scrie un program C care consta in 2 procese: 1 parinte si 1 un copil.
Parintele va citi in intregime un fisier primit ca si argument in linie de comanda
si va transmite caracterele citite catre procesul copil folosind un pipe.
Copilul va procesa informatiile primite de la parinte, va contoriza numarul de litere
mici si se va termina apeland comanda exit cu argumentul contor.
Parintele va afisa contorul la finalul executiei.*/
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

pid_t childPid;

int main(int argc, char const *argv[])
{
    int pipeFileDescriptors[2];

    if (argc < 2)
    {
        printf("INSUFICIENTE ARGUMENTE!\n");
        exit(-99);
    }

    if (pipe(pipeFileDescriptors) < 0)
    {
        printf("EROARE CREARE PIPE!\n");
        exit(-100);
    }

    childPid = fork();
    if (childPid < 0)
    {
        printf("EROARE CREARE COPIL!\n");
        exit(-1);
    }
    if (childPid == 0)
    {
        close(pipeFileDescriptors[1]);
        int store, count = 0;
        char buffer[8];
        while ((store = read(pipeFileDescriptors[0], buffer, 8)))
        {
            for (int i = 0; i < store; i++)
            {
                if (buffer[i] >= 'a' && buffer[i] <= 'z')
                {
                    count++;
                }
            }
        }
        close(pipeFileDescriptors[0]);
        exit(count);
    }
    else
    {
        close(pipeFileDescriptors[0]);
        int fileDescriptor = open(argv[1], O_RDONLY);
        int store;
        char buffer[8];
        while ((store = read(fileDescriptor, buffer, 8)))
        {
            write(pipeFileDescriptors[1], buffer, store);
        }
        close(pipeFileDescriptors[1]);
    }
    int status;
    wait(&status);
    printf("CHILD EXIT WITH STATUS: %d", WEXITSTATUS(status));
    return 0;
}

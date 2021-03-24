/*Problema 2:
Sa se scrie un program C care consta in mai multe procese: parinte si 3 copii.

Primul copil va citi in intregime un fisier primit ca si argument in linie de comanda
si va transmite caracterele citite catre al doilea si al treilea copil folosind 
mecanismul de pipe.

Copilul al doilea va contoriza numarul de litere mici.

Copilul al treilea va contoriza numarul de cifre.

Copilul al doilea si al treilea se vor termina apeland exit cu argumentul contor.

Parintele va afisa contoarele extrase de la copii la finalul executiei.*/
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

pid_t childPid1, childPid2, childPid3;

int main(int argc, char const *argv[])
{
    int pipe1FileDescriptors[2];
    int pipe2FileDescriptors[2];

    if (argc < 2)
    {
        printf("INSUFICIENTE ARGUMENTE!\n");
        exit(-99);
    }

    if (pipe(pipe1FileDescriptors) < 0)
    {
        printf("EROARE CREARE PIPE!\n");
        exit(-100);
    }

    if (pipe(pipe2FileDescriptors) < 0)
    {
        printf("EROARE CREARE PIPE!\n");
        exit(-100);
    }

    childPid1 = fork();
    if (childPid1 < 0)
    {
        printf("EROARE CREARE COPIL!\n");
        exit(-1);
    }
    if (childPid1 == 0)
    {
        close(pipe1FileDescriptors[0]);
        close(pipe2FileDescriptors[0]);
        int fileDescriptor = open(argv[1], O_RDONLY);
        int store;
        char buffer[8];
        while ((store = read(fileDescriptor, buffer, 8)))
        {
            write(pipe1FileDescriptors[1], buffer, store);
            write(pipe2FileDescriptors[1], buffer, store);
        }
        close(pipe1FileDescriptors[1]);
        close(pipe2FileDescriptors[1]);
        close(fileDescriptor);
        exit(1);
    }

    childPid2 = fork();
    if (childPid2 < 0)
    {
        printf("EROARE CREARE COPIL 2\n");
        exit(-2);
    }
    if (childPid2 == 0)
    {
        close(pipe1FileDescriptors[1]);
        close(pipe2FileDescriptors[1]);
        int store, count = 0;
        char buffer[8];
        while ((store = read(pipe1FileDescriptors[0], buffer, 8)))
        {
            for (int i = 0; i < store; i++)
            {
                if (buffer[i] >= 'a' && buffer[i] <= 'z')
                {
                    count++;
                }
            }
        }
        close(pipe1FileDescriptors[0]);
        close(pipe2FileDescriptors[0]);
        exit(count);
    }

    childPid3 = fork();
    if (childPid3 < 0)
    {
        printf("EROARE CREARE COPIL 3\n");
        exit(-2);
    }
    if (childPid3 == 0)
    {
        close(pipe1FileDescriptors[1]);
        close(pipe2FileDescriptors[1]);
        int store, count = 0;
        char buffer[8];
        while ((store = read(pipe2FileDescriptors[0], buffer, 8)))
        {
            for (int i = 0; i < store; i++)
            {
                if (buffer[i] >= '0' && buffer[i] <= '9')
                {
                    count++;
                }
            }
        }
        close(pipe1FileDescriptors[0]);
        close(pipe2FileDescriptors[0]);
        exit(count);
    }

    close(pipe1FileDescriptors[0]);
    close(pipe1FileDescriptors[1]);
    close(pipe2FileDescriptors[0]);
    close(pipe2FileDescriptors[1]);

    int status1, status2, status3;
    waitpid(childPid1, &status1, 0);
    waitpid(childPid2, &status2, 0);
    waitpid(childPid3, &status3, 0);

    printf("CHILD 2 NUMBER OF SMALL LETTERS: %d\n", WEXITSTATUS(status2));
    printf("CHILD 3 NUMBER OF DIGITS: %d\n", WEXITSTATUS(status3));
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>

int* fibonacci(int n)
{
    int n0 = 0;
    int n1 = 1;

    int* v = malloc(n * sizeof(int));

    for(int i = 0; i < n; i++)
    {
        v[i] = n0; 

        int aux = n0;
        n0 = n1;
        n1 += aux;
    }

    return v;
}

int main(int argc, char *argv[])
{
    if (argc != 2 || atoi(argv[1]) < 0) 
    {
        printf("Invalid input \n");
        return 1;
    }

    int n = atoi(argv[1]);

    const int SIZE = sizeof(int) * n;
    const char *name = "FibValues";

    int fd = shm_open(name, O_CREAT | O_RDWR, 0666);

    ftruncate(fd, SIZE);

    int *ptr = (int *) mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    pid_t pid = fork();

    if(pid < 0)
    {
        fprintf(stderr, "Fork Failed");
        return 1;
    }
    else if(pid == 0)
    {
        int *v = fibonacci(n);
        memcpy(ptr, v, SIZE);
    }
    else
    {
        wait(NULL);

        for(int i = 0; i < n; i++)
        {
            printf("%d ", ptr[i]);
        }

        printf("\n");
        shm_unlink(name);
    }

    return 0;
}

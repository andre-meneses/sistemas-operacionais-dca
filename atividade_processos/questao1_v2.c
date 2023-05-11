#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

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
    int n = atoi(argv[1]);
    int *v;

    if(n >= 0) 
        v = fibonacci(n);
    else 
    {
        printf("Invalid input: n must not be negative \n");
        return 1;
    }
        
    pid_t pid = fork();

    if(pid < 0)
    {
        fprintf(stderr, "Fork Failed");
        return 1;
    }
    else if (pid == 0)
    {
        for(int i = 0; i < n;i++) printf("%d ", v[i]);
        printf("\n");
    }
    else
    {
        wait(NULL);
        printf("Child Complete \n");
    }

    return 0;
}

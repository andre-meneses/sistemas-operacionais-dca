#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


int validate_input(int argc, char *argv[])
{
    if(argc != 2) 
    {
        printf("Invalid input: Please provide exactly one argument. \n");
        return 0;
    }

    int n = atoi(argv[1]); 

    if(n < 0) 
    {
        printf("Invalid input: n must be greater than 0 \n");
        return 0;
    }

    return 1;
}

int main(int argc, char *argv[])
{
    pid_t pid = fork();

    if(pid < 0)
    {
        fprintf(stderr, "Fork Failed");
        return 1;
    }
    else if (pid == 0)
    {
        if (validate_input(argc, argv))
            execlp("./fibonacci", "fibonacci", argv[1], (char *) NULL);
    }
    else
    {
        wait(NULL);
        printf("Child Complete \n");
    }

    return 0;
}

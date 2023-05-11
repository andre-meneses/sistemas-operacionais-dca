#include <stdio.h>
#include <stdlib.h>

void fibonnaci(int n)
{
    int n0 = 0;
    int n1 = 1;

    for(int i = 0; i < n; i++)
    {
        printf("%d ", n0);

        int aux = n0;
        n0 = n1;
        n1 += aux;
    }

    printf("\n");
}

int main(int argc, char* argv[])
{
    fibonnaci(atoi(argv[1]));
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[])
{
    int pid = fork(), n;

    if (pid)
    {
        n = 6;
        wait();
    }
        //fork();

    else
        n = 1;

    for (int i = n; i < n + 5; i++)
    {
        printf("%d ", i);
        fflush(stdout);
    }

    if (pid)
        printf("\n");
}
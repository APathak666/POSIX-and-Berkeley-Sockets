#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
    int fd[2];

    if(pipe(fd) == -1 )
    {
        printf("An error occurred while opening the pipe\n");
        return 1;
    }

    int id = fork();

    if (id == 0)
    {
        close(fd[0]);
        int x;
        printf("Enter a number: ");
        scanf("%d", &x);
        write(fd[1], &x, sizeof(int));
        close(fd[1]);
    }

    else
    {
        close(fd[1]);
        int x;
        read(fd[0], &x, sizeof(int));
        close(fd[0]);
        printf("Received %d from child process\n", x);
    }
}
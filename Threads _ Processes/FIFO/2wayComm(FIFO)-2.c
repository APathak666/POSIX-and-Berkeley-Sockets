#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

int main(int argc, char* argv[])
{
    if (mkfifo("samplefifo", 0777) == -1)
    {
        if (errno != EEXIST)
        {
            printf("Could not create file");
            return 1;
        }
    }

    printf("rOpening...\n");
    int fd = open("2wayfifo", O_RDONLY);

    printf("Reading...\n");
    int x;
    read(fd, &x, sizeof(int));

    printf("Initial value: %d\n", x);

    printf("rClosing...\n");
    close(fd);

    x = x*x;

    printf("wOpening...\n");
    fd = open("2wayfifo", O_WRONLY);

    printf("Writing...\n");
    write(fd, &x, sizeof(int));

    printf("wClosing...\n");
    close(fd);
}
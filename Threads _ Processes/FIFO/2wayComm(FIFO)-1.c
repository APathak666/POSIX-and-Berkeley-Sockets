#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <time.h>

int main(int argc, char* argv[])
{
    if (mkfifo("2wayfifo", 0777) == -1)
    {
        if (errno != EEXIST)
        {
            printf("Could not create file");
            return 1;
        }
    }

    printf("wOpening...\n");
    int fd = open("2wayfifo", O_WRONLY);
    
    srand(time(NULL));
    int x = rand() % 100;

    printf("Writing...\n");
    write(fd, &x, sizeof(int));

    printf("wClosing...\n");
    close(fd);

    printf("rOpening...\n");
    fd = open("2wayfifo", O_RDONLY);

    printf("Reading...\n");
    read(fd, &x, sizeof(int));

    printf("Squared value: %d\n", x);
}
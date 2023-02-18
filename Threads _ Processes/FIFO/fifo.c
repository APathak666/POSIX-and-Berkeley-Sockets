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

    int fd = open("samplefifo", O_WRONLY);
    int x = 97;

    write(fd, &x, sizeof(int));
    close(fd);
}
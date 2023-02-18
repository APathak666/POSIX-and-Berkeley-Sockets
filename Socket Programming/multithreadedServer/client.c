#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdarg.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <pthread.h>

int main(int argc, char* argv[])
{
    char DATA[1024];// = "Half a league, half a league . . .";
    int sock;
    struct sockaddr_in server;
    struct hostent *hp, *gethostbyname();
    char buf[1024];
    int rval;

    /* Create socket */
    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 0)
    {
        perror("opening stream socket");
        exit(1);
    }
    /* Connect socket using name specified by command line. */

    server.sin_family = AF_INET;
    hp = gethostbyname(argv[1]);

    printf("%s\n", hp->h_name);

    if (hp == 0)
    {
        fprintf(stderr, "%s: unknown host", argv[1]);
        exit(2);
    }

    bcopy(hp->h_addr, &server.sin_addr, hp->h_length);
    server.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (struct sockaddr*) &server, sizeof(server)) < 0)
    {
        perror("connecting stream socket");
        printf("%d\n", errno);
        exit(1);
    }

//    char str[1024];

    while (1)
    {
        printf("Enter data to send server: ");
        scanf("%[^\n]s", DATA);
        getchar();
        //printf("%s\n", DATA);

        if (write(sock, DATA, sizeof(DATA)) < 0)
            perror("writing on stream socket");

       printf("Successfully sent message: %s\n", DATA);

        // bzero(buf, sizeof(buf));

        // if ((rval = read(sock, buf, 1024)) < 0)
        //     perror("reading stream message");

        // else
        // {
        //     printf("-->%s\n", buf);

        //     time_t t;
        //     time(&t);
        //     printf("Received at: %s\n", ctime(&t));
        // }
 
    }

    // if (rval == 0)
    //     printf("Ending connection\n");

    // close(sock);
}
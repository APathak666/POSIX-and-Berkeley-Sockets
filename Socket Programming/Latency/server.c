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
#include <signal.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

#define sDATA "server2client sample"

double timeInMilliseconds(void);

int main(int argc, char* argv[])
{
    double delays[400];
    for (int i = 0; i < 400; i++)
        delays[i] = 0;

    int sock, length;
    struct sockaddr_in server;
    int msgsock;
    double rec, curr;
    char DATA[1024];
    char buf[1024];
    int rval;
    /* Create socket */

    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 0)
    {
        perror("opening stream socket");
        exit(1);
    }

    /* Name socket using wildcards */
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = 0;

    if (bind(sock, (struct sockaddr*) &server, sizeof(server)))
    {
        perror("binding stream socket");
        exit(1);
    }

    /* Find out assigned port number and print it out */
    length = sizeof(server);
    if (getsockname(sock, (struct sockaddr*) &server, &length))
    {
        perror("getting socket name");
        exit(1);
    }

    printf("Socket has port #%d\n", ntohs(server.sin_port));

    /* Start accepting connections */
    listen(sock, 5);

    for (int i = 0; i < 400; i++)
    {
        msgsock = accept(sock, 0, 0);

        if (msgsock == -1)
            perror("accept");
    
        else do
        {
            bzero(buf, sizeof(buf));

            if ((rval = read(msgsock, (void *) &rec, sizeof(rec))) < 0)
                perror("reading stream message");
    
            if (rval == 0)
            {
                //shutdown(sock, 2);
                //break;
                printf("Ending connection\n");
                double av = 0;

                for (int i = 0; i < 400; i++)   
                    printf("%lf ", delays[i]);

                for (int i = 1; i < 400; i++)
                    av += delays[i];

                printf("%lf\n", av);
                av /= 400;
                printf("Average latency: %lf\n", av);

                for (int i = 0; i < 400; i++)
                    delays[i] = 0;
            }

            else
            {
                printf("Received: %lf\n", rec);
                curr = timeInMilliseconds();
                delays[i] = curr - rec;
                printf("Current time: %lf | Time from client send: %lf\n", curr, delays[i]);
                printf("%lf\n", delays[i] + 4);
            }

            printf("Sending client data...");
//            scanf("%[^\n]s", DATA);
//            getchar();

            curr = timeInMilliseconds();

            if (write(msgsock, (void *) &curr, sizeof(curr)) < 0)
                perror("writing on stream socket");

            printf("Sent at: %lf\n", curr);        
        } while (rval != 0);
    }
}

double timeInMilliseconds(void) {
    struct timeval tv;

    gettimeofday(&tv,NULL);
    return (((double)tv.tv_sec)*4000)+(tv.tv_usec/4000);
}
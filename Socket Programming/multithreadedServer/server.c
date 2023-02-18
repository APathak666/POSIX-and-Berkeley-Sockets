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
#include "linked_list.c"

#define loopback "127.0.0.1"
#define listenPort 9999
#define THREADPOOL_SIZE 10

pthread_t pool[THREADPOOL_SIZE];
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_var = PTHREAD_COND_INITIALIZER;

void check(int test, char* str)
{
    if (test < 0)
    {
        perror(str);
        printf("%d %d\n", test, errno);
        exit(1);
    }

    else
        printf("%s\n", str);
}

void* connHandler(void* client_sock)
{
    int sock = * (int*) client_sock;
    free(client_sock);
    char buf[1024];
    size_t bytes_read;

    do
    {
        memset(buf, 0, sizeof(buf));

        check(bytes_read = read(sock, buf, sizeof(buf)), "Receiving from client");

        if (!bytes_read)
            printf("Ending connection...\n");

        else
            printf("Received from client-->%s\n", buf);
    } while (bytes_read);
}

void* threadHandler(void* arg)
{
    printf("created thread\n");
    while (1)
    {
        pthread_mutex_lock(&mtx);
        int* client = dequeue();
        if (client == NULL)
        {
            pthread_cond_wait(&cond_var, &mtx);
            client = dequeue();
        }

        pthread_mutex_unlock(&mtx);

        if (client != NULL)
        {
            connHandler((void*) client);
            printf("passed to connection handler\n");
        }
        // else
        //     printf("nothing available in queue to read\n");
    }
}

int main()
{
    int sock, mesgsock;
    socklen_t addr_size = sizeof(struct sockaddr);
    struct sockaddr_in server, client;

    for (int i = 0; i < THREADPOOL_SIZE; i++)
        pthread_create(&pool[i], NULL, threadHandler, NULL);

    check(sock = socket(AF_INET, SOCK_STREAM, 0), "Opening stream socket");

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(loopback);
    server.sin_port = htons(listenPort);

    check(bind(sock, (struct sockaddr*) &server, sizeof(server)), "Binding stream socket");
    check(listen(sock, 5), "Listening");

    while(1)
    {
        check((mesgsock = accept(sock, (struct sockaddr*) &client, &addr_size)), "Accepting connection");
        //connHandler(mesgsock);

        int* sock_cli = malloc(sizeof(int));
        if (sock_cli == NULL) printf("malloc failed\n");
        *sock_cli = mesgsock;

        pthread_mutex_lock(&mtx);
        enqueue(sock_cli);
        pthread_cond_signal(&cond_var);
        // printList();
        pthread_mutex_unlock(&mtx);

        // pthread_create(&connector, NULL, connHandler, (void *) sock_cli);
    }
}

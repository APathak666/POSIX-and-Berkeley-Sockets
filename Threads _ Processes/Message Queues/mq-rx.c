#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <string.h>

#define MQ_NAME "/message_queue"

typedef struct
{
    char msg[88];
} message;

int main(void)
{
    struct mq_attr attributes  = 
    {
        .mq_flags = 0,
        .mq_maxmsg = 10,
        .mq_curmsgs = 0,
        .mq_msgsize = sizeof(message)
    };

    mqd_t queue = mq_open(MQ_NAME, O_CREAT | O_RDONLY | S_IRUSR | S_IWUSR | O_NONBLOCK, &attributes);

    message rec;

    int bytes_read = mq_receive(queue, (char*) &rec, sizeof(rec), NULL);
    printf("%s\n", rec.msg);
    printf("%d\n", bytes_read);
    printf("Successfully received message. Closing now...\n");
    getchar();
}

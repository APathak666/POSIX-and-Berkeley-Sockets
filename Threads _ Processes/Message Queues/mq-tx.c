#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

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

    mqd_t queue = mq_open(MQ_NAME, O_CREAT | O_WRONLY | S_IRUSR | S_IWUSR, &attributes);

    message text;
    strcpy(text.msg, "Test");

    int bytes_sent = mq_send(queue, (const char *) &text, sizeof(text), 1);
    printf("%d\n", bytes_sent);
    printf("%d", errno);
    printf("Successfully inserted message into queue. Closing now...\n");
    getchar();
}

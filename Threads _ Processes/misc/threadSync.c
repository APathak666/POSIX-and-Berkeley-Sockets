#include <stdio.h>
#include <pthread.h>

#define NUMLOOPS 500000000

long long sum = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* counter (void* arg)
{
    int offset = *(int*) arg;

    for (int i = 0; i < NUMLOOPS; i++)
    {
        pthread_mutex_lock(&mutex);
        sum += offset;
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

int main()
{
    int offset1 = 1;
    pthread_t thread1;
    pthread_create(&thread1, NULL, counter, &offset1);

    int offset2 = -1;
    pthread_t thread2;
    pthread_create(&thread2, NULL, counter, &offset2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Sum: %lld\n", sum);
}
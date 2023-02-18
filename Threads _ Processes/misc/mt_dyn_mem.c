#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// The sum computed by the background thread
long long sum = 0;

// Thread function to generate sum of 0 to N
void* sum_runner(void* arg)
{
	long long *limit_ptr = (long long*) arg;

	for (long long i = 0; i <= *limit_ptr; i++)
		sum += i;


	long long* answer = malloc(sizeof(long long*));
    *answer = sum;
	pthread_exit(answer);
}

int main(int argc, char **argv)
{
	if (argc < 2) {
		printf("Usage: %s <num>\n", argv[0]);
		exit(-1);
	}

	long long limit = atoll(argv[1]);

	// Thread ID:
	pthread_t tid;

	// Create attributes
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	pthread_create(&tid, &attr, sum_runner, &limit);

    long long* answer;

    pthread_join(tid, (void **) &answer);
	// Wait until thread is done its work
	printf("Sum is %lld\n", *answer);
    free(answer);
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

struct params
{
	long long limit;
	long long answer;
};

void* threadFunc (void* limit_pt)
{
	struct params* arg = (struct params*) limit_pt;
 
	long long sum = 0;
	for (long long i = 1; i <= arg->limit; i++)
		sum += i;

	arg->answer = sum;
	pthread_exit(0);
}

int main(int argc, char* argv[])
{
	long long limit;
	int thread_count = argc - 1;

	pthread_t tid0;//, tid1, tid2;
	pthread_t threads[thread_count];// = {&tid0, &tid1, &tid2};

	struct params arg[thread_count];

	for (int i = 0; i < thread_count; i++)
	{
		arg[i].limit = atoll(argv[i + 1]);
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&threads[i], &attr, threadFunc, &arg[i]);
	}

	for (int i = 0; i < thread_count; i++)
	{
		pthread_join(threads[i], NULL);
		printf("%lld\n", arg[i].answer);
	}
}
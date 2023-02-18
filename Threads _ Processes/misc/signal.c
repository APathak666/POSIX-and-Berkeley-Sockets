#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handler(int num)
{
	write(STDOUT_FILENO, "I won't die!", 13);
}

int main()
{
	signal(SIGINT, handler);
	signal(SIGTERM, handler);
	while (1)
	{
		printf("Wasting your cycles. %d\n", getpid());
		sleep(1);
	}
}

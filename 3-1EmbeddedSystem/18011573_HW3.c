#include<stdio.h> // to use printf()
#include<signal.h> // to use signal(), SIGINT
#include<sys/types.h> // to use datatype pid_t
#include<unistd.h> // to use fork()
#include<stdlib.h> // to use exit

void childSignalHandler(int signal)
{
	printf("exit child\n");
	exit(0);
}
void parentSignalHandler(int signal)
{
	printf("exit parent\n");
	exit(0);
}


int main()
{
	pid_t parentp_id;
	pid_t childp_id;
	pid_t grandchildp_id;

	parentp_id = getpid();
	printf("I'm parent\n");
	printf("parent pid : %d\n", parentp_id);

	parentp_id = fork();

	if (parentp_id == 0) // parent process ---> child process
	{
		childp_id = getpid();
		printf("I'm child\n");
		printf("child pid : %d\n", childp_id);

		// current parentp_id : 0 ---> parent process id
		parentp_id = getppid();

		childp_id = fork();
		if (childp_id == 0) // child process ---> grandchild process
		{
			grandchildp_id = getpid();
			printf("I'm grandchild\n");
			printf("grandchild pid : %d\n", grandchildp_id);

			// current childp_id : 0 ---> child process id
			childp_id = getppid();
			printf("exit grandchild\n");
			sleep(1);
			kill(childp_id, SIGINT);
			sleep(1);
			kill(parentp_id, SIGINT);
		}
		else if (childp_id >= 0) // child process ---> child process
		{
			// current childp_id : grandchild process id ---> child process id
			childp_id = getpid();
			while (1)
			{
				sleep(1);
				signal(SIGINT, childSignalHandler);
			//	printf("child waiting\n");
			}
		}
		else 
		{
			printf("error occured!\n");
		}
	}
	else if (parentp_id >= 0) // parent process ---> parent process
	{
		// current parentp_id : child process id ---> parent process id
		parentp_id = getpid();
		while (1)
		{
			sleep(1);
			signal(SIGINT, parentSignalHandler);
		//	printf("parent waiting\n");
		}
	}
	else
	{
		printf("error occured!\n");
	}

	return 0;
}

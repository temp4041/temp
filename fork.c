#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
	pid_t pid;
	pid = fork();

	if (pid < 0)
	{
		fprintf(stderr, "Couldn't create child process\n");
	}
	else if (pid == 0)
	{
		// Represents child process
		printf("Parent PID: %d Child PID (Active): %d\n", getppid(), getpid());
	}
	else 
	{
		int status;
	
		// Represents parent process
		printf("Parent PID (Active): %d Child PID: %d\n", getpid(), pid);
		waitpid(pid, &status, 0);
		printf("Child process finished\n");
	}
	

	// Wait for child process to finish

	//	wait(&status);



	return 0;

}

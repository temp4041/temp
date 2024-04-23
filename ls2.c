#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

int main()
{
	DIR *directory;
	struct dirent *entry;

	directory = opendir(".");
	if (directory == NULL)
	{
		perror("Error reading directory");
	}

	while((entry = readdir(directory)) != NULL)
	{
		printf("%s\n", entry->d_name);
	}	
	
	closedir(directory);
	return 0;
}

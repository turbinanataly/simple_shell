#include <string.h>
#include <unistd.h>
#include "command_shell.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdbool.h>

static int main_cycle(int fd)
{
	bool is_exit = false;
	while(!is_exit)
	{
		shell_command* command = NULL;
		
		if(get_shell_command(&command, fd, &is_exit) == 0)
		{
			execute_shell_command(command);
			free_shell_command(command);
		}
	}
	return 0;
}

int main(int argc, char** argv)
{
	int fd = 0;

	if(argc == 1)
	{
		main_cycle(fd);
	}
	else if(argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if(fd < 0)
		{
			perror("Error open file");
			return -1;
		}
		main_cycle(fd);
		close(fd);
	}
	else
	{
		printf("Error count arguments\n");
		return -1;
	}
	
	return 0;
}


#include <string.h>
#include <unistd.h>
#include "command_shell.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>

#define BUFF_SIZE 255

int test_print(int fd)
{
	int p_in_buff = 0;
	int count_buff = 1;
	char* command_buff = (char*)malloc(sizeof(char)*(BUFF_SIZE+1));
	char* char_buff = (char*)malloc(sizeof(char));
	char* realloc_buff = NULL;

	while(read(fd, char_buff, 1))
	{
		if(char_buff[0] == '\n' || char_buff[0] == EOF)
		{
			command_buff[p_in_buff] = '\0';
			shell_command* command;
			pid_t pid;
			if((pid = fork()) == 0)
			{
				printf("0 pid = %d\n", (int) pid);
				get_shell_command(&command,command_buff);
				execute_shell_command(command);
			}
			printf("par start pid = %d\n", (int)pid);
			waitpid(pid, NULL, 0);
			printf("par end pid = %d\n", (int)pid);
			free_shell_command(command);
			free(command_buff);
			p_in_buff = 0;
			count_buff = 1;
			command_buff = (char*)malloc(sizeof(char)*(BUFF_SIZE+1));	
		}
		else
		{
			if(p_in_buff < BUFF_SIZE*count_buff)
			{
				command_buff[p_in_buff] = char_buff[0];
				p_in_buff++;
			}
			else
			{
				realloc_buff = (char*)realloc(command_buff,sizeof(char)*BUFF_SIZE);
				if(realloc_buff != NULL)
				{
					command_buff = realloc_buff;
					command_buff[p_in_buff] = char_buff[0];
					p_in_buff++;
					count_buff++;
				}
			}
		}
	}
	return 0;
}

int main(int argc, char** argv)
{
	if(argc == 1)
	{
		test_print(0);
	}
	else if(argc == 2)
	{
		printf("%s\n", argv[1]);
		int fd = open(argv[1], O_RDONLY);
		test_print(fd);
		close(fd);
	}
	else
	{
		printf("Error count arguments");
		return -1;
	}
	
	/*shell_command* command;
	const char* test = "/bin/ls";
	char* str_comm = (char*)malloc((strlen(test)+1)*sizeof(char));
	strcpy(str_comm, test);

	get_shell_command(&command, str_comm);
	execute_shell_command(command);
	free_shell_command(command);

	 test = "/user/bin/touch   test_shell.txt";
          str_comm = (char*)malloc((strlen(test)+1)*sizeof(char));
         strcpy(str_comm, test);
        
        get_shell_command(&command, str_comm);
        execute_shell_command(command);
        free_shell_command(command);

 	 test = "/bin/ls";
         str_comm = (char*)malloc((strlen(test)+1)*sizeof(char));
         strcpy(str_comm, test);
        
        get_shell_command(&command, str_comm);
        execute_shell_command(command);
        free_shell_command(command);
	*/
	return 0;
}


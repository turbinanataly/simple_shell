#include "command_shell.h"

int get_shell_command(shell_command** comm, int fd, bool* is_exit)
{
	char curr_char = '0';
	char* string_command = (char*)malloc(sizeof(char*) * (BUFF_SIZE +1));
	int count_buff = 1;
	int curr_p = 0;
	int read_count = 0;
	shell_command* command;
	int word_len = 0;
	int i = 0;
	int command_len = 0; 
	int i_word = 0;
	char* curr_point = string_command;
	
	while(1)
	{
		read_count = read(fd, &curr_char, 1);
		if(curr_char == '\n' || read_count != 1)
		{
			*is_exit = (read_count != 1);
			string_command[curr_p] = '\0';
			printf("string_command: %s\n", string_command);
			break;
		}
		else
		{
			if(curr_p < BUFF_SIZE*count_buff)
			{
				string_command[curr_p] = curr_char;
				curr_p++;
			}
			else
			{
				count_buff++;
				string_command = (char*)realloc(string_command, sizeof(char)*(BUFF_SIZE * count_buff + 1));
				string_command[curr_p] = curr_char;
				curr_p++;
			}
		}
	}
	
	command_len = strlen(string_command);
	if(command_len == 0)
		return -1;
	
        command = (shell_command*)malloc(sizeof(shell_command));
	command->argc = 0;

	if(string_command[0] != ' ')
	{
		command->argc = 1;
	}

	for(i = 1; i < command_len; i++)
	{
		if(string_command[i] != ' ' && string_command[i-1] == ' ')
		{
			command->argc++;
		}
	}
	
	command->argv = (char**)malloc(sizeof(char*)*(command->argc +1));
	
	for(i = 0; i < command_len; i++)
        {
                if(string_command[i] != ' ')
		{
			word_len++;
			if(i != 0 && string_command[i-1] == ' ')
			{
				curr_point = &string_command[i];
			}
		}
		else if(i != 0 && string_command[i-1] != ' ')
		{
			command->argv[i_word] = (char*)malloc(sizeof(char)*(word_len + 1));
                        strncpy(command->argv[i_word], curr_point, word_len);
			command->argv[i_word][word_len] = '\0';
                        word_len = 0;
                        i_word++;
		}
        }

	if(word_len != 0)
	{
		command->argv[i_word] = (char*)malloc(sizeof(char)*(word_len + 1));
		strncpy(command->argv[i_word], curr_point, word_len);
		command->argv[i_word][word_len] = '\0';
		word_len = 0;
		i_word++;
	}

	command->argv[command->argc] = 0;
	*comm = command;
        return 0;
}

int free_shell_command(shell_command* command)
{
	int i;
	if(command)
	{
		if(command->argv)
		{
			for(i = 0; i < command->argc; i++)
        		{
				free(command->argv[i]);
        		}
		
			free(command->argv);
		}
		free(command);
	}
	return 0;
}

int execute_shell_command(shell_command* command)
{
	if(command != NULL && command->argc > 0)
	{
		pid_t pid;
		if(!(pid = fork()))
		{
			execv(command->argv[0], command->argv);
			perror("wrong command");
			exit(-1);
		}
		int status = 0;
		waitpid(pid, &status, 0);	
	}
	return 0;
}

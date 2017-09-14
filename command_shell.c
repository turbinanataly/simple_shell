#include "command_shell.h"

int get_shell_command(shell_command** comm, char* string_command)
{
	shell_command* command;
	int word_len = 0;
	int i = 0;
	int command_len = strlen(string_command);
	int i_word = 0;
	char* curr_point = string_command;
	
	if(command_len == 0)
		return -1;
	
        command = (shell_command*)malloc(sizeof(shell_command));
	command->argc = 0;
	
	for(i = 0; i < command_len; i++)
	{
		if(i == 0)
		{
			if(string_command[i] != ' ')
			{
				command->argc = 1;
			}
		}
		else if(string_command[i] != ' ' && string_command[i-1] == ' ')
		{
			command->argc++;
		}
	}
	
	command->argv = (char**)malloc(sizeof(char*)*command->argc);
	
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
			command->argv[i_word] = (char*)malloc(sizeof(char)*word_len);
                        strncpy(command->argv[i_word], curr_point, word_len);
                        word_len = 0;
                        i_word++;
		}

		if(i == command_len - 1 && word_len != 0)
		{
			command->argv[i_word] = (char*)malloc(sizeof(char)*word_len);
                        strncpy(command->argv[i_word], curr_point, word_len);
                        word_len = 0;
                        i_word++;
		}	
        }
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
		execv(command->argv[0], command->argv);
	}
	return 0;
}

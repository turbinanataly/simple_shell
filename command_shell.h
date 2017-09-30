#ifndef __COMMAND_SHELL__
#define __COMMAND_SHELL__

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdbool.h>

#define BUFF_SIZE 255

typedef struct { 
        int argc; 
        char** argv; 
} shell_command; 
 
int get_shell_command(shell_command** command, int fd, bool* is_exit); 
int free_shell_command(shell_command* command); 
int execute_shell_command(shell_command* command); 

#endif /*__COMMAND_SHELL__*/


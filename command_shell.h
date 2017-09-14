#ifndef __COMMAND_SHELL__
#define __COMMAND_SHELL__

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct { 
        int argc; 
        char** argv; 
} shell_command; 
 
int get_shell_command(shell_command** command, char* string_command); 
int free_shell_command(shell_command* command); 
int execute_shell_command(shell_command* command); 

#endif /*__COMMAND_SHELL__*/

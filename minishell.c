#include <readline/readline.h> // readline
#include <readline/history.h> // history
#include <stdbool.h> // bools
#include <stdlib.h> // malloc e free
#include <stdio.h>  // printf

int main(void)
{
    char    *cmd;

    while (true)
    {
        cmd = readline("Pocaterra pocaterra tchuuuuu 🚆: ");

        if (!cmd)
            break;

        if (*cmd)
            add_history(cmd);
        
        printf("Escreveste: %s\n", cmd);
        
        free(cmd);
    }

    return (0);
}

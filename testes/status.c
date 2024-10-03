#include <stdio.h> 
#include <stdlib.h> // exit and wte
#include <unistd.h> // fork
#include <sys/wait.h>

int main(void)
{
    pid_t   pid;

    pid = fork();

    if (pid < 0)
        return -1;
    if (pid == 0)
    {
        // filho
        sleep(4);
    }
    else
    {
        // pai
        int status;
        int result;
        while (1)
        {
            result = waitpid(pid, &status, WNOHANG);
            if (result == 0) // o processo filho com o pid ainda nao acabou
            {
                printf("ainda nao acabei papa\n ");
                sleep(2);
            }
            else if (result == pid) // o processo filho terminou
            {
                if ( WIFEXITED(status))
                {
                    printf("WIFEXITED : %d\nStatus : %d\n", WIFEXITED(status), WEXITSTATUS(status));
                    break ;
                }
            }
            else // waitpid deu erro
            {
                perror("Erro no wait\n");
                exit (-1);
            }
        }
    }
    return 0;
}
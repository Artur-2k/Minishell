#include <unistd.h> // write read pipe
#include <sys/wait.h> // wait
#include <sys/types.h> //pid_t
#include <string.h> // strlen
#include <stdlib.h> // malloc e free
#include <stdio.h> // printf()


// Programa que recebe do processo filho uma string e a imprime no STDOUT
int main()
{
    int pipefd[2];
    pid_t pid;
    
    if (pipe(pipefd) == -1) // Failed
        return -1;

    pid = fork();
    if (pid < 0) // Failed
        return -2;
    else if (pid == 0) // Child
    {
        close(pipefd[0]); // Closing reading end
        char *string = "Ola mundo maluco!\n";
        int n = strlen(string);

        //passing the size of the string as the first 4 bytes
        if (write(pipefd[1], &n, sizeof(int)) < 0) 
        {
            close(pipefd[1]); // Closing writing end
            return -3;
        }
        // and then passing the string
        if (write(pipefd[1], string, sizeof(char) * n) < 0)
        {
            close(pipefd[1]); // Closing writing end
            return -4;
        }
        close(pipefd[1]); // Closing writing end
    }
    else // Parent
    {
        close(pipefd[1]); // Closing writing end
        int n;

        if (read(pipefd[0], &n, sizeof(int)) < 0)
        {
            close(pipefd[0]);
            return -6;
        }
        char *str = malloc(sizeof(char) * n + 1);
        if (!str)
        {
            close(pipefd[0]);
            return -5;
        }
        read(pipefd[0], str, n);
        str[n + 1] = '\0';
        printf("A STRING DO CHILD FOI: %s", str);
        free(str);
        close(pipefd[0]); // Closing reading end
    }
    wait(NULL);
    return 0;
}

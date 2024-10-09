#ifndef MINISHELL_H
#define MINISHELL_H

#include <errno.h> // errorno
#include <stdio.h> // printf perror
#include <unistd.h> // read fork getcwd() chdir()
#include <sys/wait.h> // wait waitpid wait3 wait4 WIFEXITED WEXITSTATUS
#include <sys/types.h> //pid_t
#include <fcntl.h> // open close fd
#include <termio.h> // terminal config
#include <signal.h> // signal handling
#include <readline/readline.h> // readline
#include <readline/history.h> // addhistory
#include <stdlib.h> // malloc free size_t...
#include <stdbool.h> // bool -- we could use bitwise too for flags
#include <../libft/libft.h> // libft

// Argument types
enum e_token_types
{
    // Redirects
    R_IN = 1,
    R_OUT = 2,
    R_OUT_APP = 3,
    HEREDOC = 4,
    // Pipe
    PIPE = 5,
    // Command
    CMD = 6,
    ARG = 7,
    // File
    FUCKING_FILE = 8
};

// Argument nodes
typedef struct  s_token_list
{
    struct s_arg_dlist  *prev;
    struct s_arg_dlist  *next;

    // type of token
    int                 type;
    // token
    char *token;

}   t_tkn;


// root struct
typedef struct s_shell
{
    // Input
    char    *input;

    // Signals
    struct sigaction sa_int;
    struct sigaction sa_quit;
    struct sigaction sa_eof;

    t_tkn *tkn_lst_h;



}   t_shell;


// Prototypes

//Signals
void    ft_init_signals(t_shell *shell);
char    *ft_space_tokens(char *str);

#endif
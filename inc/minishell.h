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

// Color variables
#define RED \033[0;31m
#define GRN \033[0;32m
#define YEL \033[0;33m
#define BLU \033[0;34m
#define MAG \033[0;35m
#define CYN \033[0;36m
#define WHT \033[0;37m
#define RES \033[0m

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


// Env
typedef struct  s_envp
{
    struct s_envp *next;
    char *key;
    char *value;
} t_envp;


// root struct
typedef struct  s_shell
{
    // Input
    char    *input; // allocated

    // Env
    t_envp  *my_envp_h; // allocated list


    // Signals
    struct sigaction sa_int;
    struct sigaction sa_quit;


}   t_shell;


// Prototypes
//Signals
void    ft_init_signals(t_shell *shell);

// Env
void    ft_init_envp(t_shell *shell, char *envp[]);


// Tokenizer
void    ft_tokenizer(t_shell *shell);
char    **ft_split_tokens(char *str);
char    *ft_space_tokens(char *str);

#endif
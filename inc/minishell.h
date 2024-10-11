#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdarg.h> // va_start va_arg va_end
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


// Errors
typedef enum     e_errors
{
    CMD_NOT_FOUND = 1,

    PARSE_ERROR = 2
}   t_errors;

// Free helper
typedef enum    e_resource_type
{
    // basic types
    PTR = 1,

    // strings array NULL
    STR_ARR = 2,

    // env list
    ENV_PTR = 3
}   t_resource_type;

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

// Frees
void        ft_free_resources(int count, ...);

#endif
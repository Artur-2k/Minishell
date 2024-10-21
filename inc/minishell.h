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


// PIPE ENDS
#define WRITE_END 1
#define READ_END 0

// NODE TYPES
#define PIPE    1
#define EXEC    2
#define INREDIR   3
#define OUTREDIR   4
#define APPREDIR   5
#define HDREDIR   6

typedef struct s_cmd
{
    int type;
}   t_cmd;


typedef struct  s_pipe
{
    int type;

    void    *left;
    void    *right;

}   t_pipe;

typedef struct  s_redir
{
    int             type;
    
    char            *redir;
    struct s_redir  *next;
}   t_redir;

typedef struct  s_exec
{
    int type;
    
    char    **av;
    t_redir *redir_list;

}   t_exec;

// Errors
typedef enum     e_errors
{
    CMD_NOT_FOUND = 1,

    PARSE_ERROR = 2
}   t_errors;

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
    //PID
    pid_t    pid; // todo
    // Input
    char     *input; // allocated

    // Env
    t_envp   *my_envp_h; // allocated list

	// Comands
    t_cmd   *cmd_tree;
    

    // Signals
    struct sigaction sa_int;
    struct sigaction sa_quit;
}   t_shell;


// Prototypes
//Signals
void    ft_init_signals(t_shell *shell);

// Env
void    ft_init_envp(t_shell *shell, char *envp[]);
t_envp  *ft_new_node(char *envp_line);
bool    ft_has_key(char *try, int len, t_envp *envp);
char    *ft_get_value(char *key, t_envp *envp);

// Tokenizer
int     ft_tokenizer(t_shell *shell);
char    **ft_split_tokens(char *str);
char    *ft_space_tokens(char *str);
int     ft_find_syntax_errors(char **tkn_arr);
char	*ft_expand_token(char* token, t_envp *envp);

// Comand stuff
t_cmd   *ft_build(char **tkn_arr);

// Frees
void    ft_free_str_arr(char **arr);
void    ft_free_envp_lst(t_envp *my_envp);

// Utils
int 	ft_get_pid(void);

// Error
void    ft_error(); // todo
#endif
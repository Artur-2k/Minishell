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
#include "libft.h" // libft
#include <sys/stat.h> // stat


// Color variables
#define RED "\033[0;31m"
#define GRN "\033[0;32m"
#define YEL "\033[0;33m"
#define BLU "\033[0;34m"
#define MAG "\033[0;35m"
#define CYN "\033[0;36m"
#define WHT "\033[0;37m"
#define RES "\033[0m"

// Pipe Ends
#define WRITE_END   1
#define READ_END    0

// Node Types
#define PIPE        1
#define EXEC        2
#define INREDIR     3
#define OUTREDIR    4
#define APPREDIR    5
#define HDREDIR     6

// Error Types
#define EMALLOC 	1
#define ENOCMD		2

// Exit Codes
#define EXIT_FNOK   126
#define EXIT_404    127

// Typedefs
typedef struct s_envp	t_envp;
typedef	struct s_tokens	t_tokens;
typedef struct s_cmd	t_cmd;
typedef struct s_redir	t_redir;
typedef struct s_pipe	t_pipe;
typedef struct s_exec	t_exec;
typedef struct s_shell	t_shell;
typedef struct s_heredoc t_heredoc;

// Env
struct  s_envp
{
    char            *key;
    char            *value;
    struct s_envp   *next;
};

// Tokens
struct s_tokens
{
	char	*token;
	int		type;
};

// Command stuff
struct s_cmd
{
    int             type;
};

struct  s_pipe // limpar
{
    int              type;

    void            *left;
    void            *right;
};

struct  s_redir // limpar
{
    int             type;

    char            *redir; // limpar
    struct s_redir  *next;
};

struct  s_exec // limpar
{
    int             type;

    char            **av;
    t_envp          *envp; // limpar na shell only
    char            **tenvp;
    t_redir         *redir_list; // limpar
    t_shell			*shell;
};

// heredoc paths
struct s_heredoc
{
    char    *path;
    struct s_heredoc  *next;
};


// Root struct
struct  s_shell
{
    // Input
    char            *input; // allocated

    // Env
    t_envp          *my_envp_h; // allocated list
    t_envp          *envp2lol_h; // allocated list

	// Comands
    t_cmd           *cmd_tree; // allocated tree
    // helpers
    t_tokens        **tokens;

	// Exit status
	int         	status;
	unsigned char	exit_status;
    char            *sexit_status;

    // PID
    int             pid;
    char            *spid;
};

// Prototypes
//Signals
void    ft_init_signals(void);
void    ft_config_terminal(void);

void    ft_signal_restore(void);
void    ft_signal_ignore(void);

// Initializations
int		ft_init_everything(t_shell *shell, char *envp[], int ac, char **av);
int    	ft_init_envp(t_shell *shell, char *envp[]);
int     ft_init_envp2lol(t_shell *shell, char *envp[]);

// Env
char    *ft_extract_key(char *line);
char     *ft_extract_value(char *line);
t_envp  *ft_new_env_node(char *key, char *value);
t_envp  *ft_new_node(char *envp_line);
bool	ft_has_key(char *try, int len, t_envp *envp);


char    *ft_get_value(char *key, t_envp *envp);
void	ft_set_value(char *key, char *value, t_envp *envp);


// Tokenizer
int     ft_tokenizer(t_shell *shell);
char    *ft_space_tokens(char *str);
char    **ft_split_tokens(char *str);
int     ft_find_syntax_errors(char **tkn_arr);
char	*ft_expand_token(char *token, t_shell *shell);
int 	ft_emenda(char **tkn_arr, t_shell *shell);

// Command building
t_cmd   *ft_build(t_tokens **tokens, t_shell *shell);
t_cmd   *ft_build_exec(t_tokens ***tkns, t_shell *shell);
t_cmd   *ft_build_pipe(t_cmd *cmd, t_tokens **tkns ,t_shell *shell);

int     ft_redirects(t_redir *redir);

// Comand Exec
void    ft_run_cmd(t_shell *shell);
void	ft_run_tree(t_cmd *node, t_shell *shell);
int     ft_exec(t_exec *node);
void	ft_pipe(t_pipe *node, t_shell *shell);
// Comand Exec Helpers
char    *ft_check_paths_for_cmd(char **paths, char *cmd);

// Built ins
void    ft_cd(t_exec *cmd);
void	ft_echo(t_exec *cmd);
void    ft_env(t_exec *cmd);
void	ft_exit(t_exec *cmd);
void    ft_export(t_exec *cmd);
void    ft_pwd(t_exec *cmd);
void	ft_unset(t_exec *cmd);
// Built ins helper
bool	ft_is_builtin(t_cmd *cmd);
int		ft_redirect_execution(t_exec *cmd);
void	ft_run_builtin(t_exec *cmd);
int 		ft_add_entry_env(t_envp **head, char *key, char *value, int mode);
int     	ft_add_entry_env2(t_envp **head, char *key, char *value, int mode);

// Frees
void    ft_free_str_arr(char **arr);
void    ft_free_envp_lst(t_envp *my_envp);
void    ft_free_redir_list(t_redir **redirs);
void    ft_free_tree(t_cmd *tree);
void	ft_free_tokens(t_tokens **tokens);

// HEREDOCS
int     ft_heredoc_process(char **token_arr, t_shell *shell);
int     ft_theres_heredoc(t_tokens **tkns);
t_heredoc     *ft_link_heredocs(t_tokens **tkns, t_heredoc *heredoc);

// Utils
int 	ft_get_pid(void);

// Error
void	ft_what_happened(char *what, char *happend);

// Debugging
void	print_tree(t_cmd *cmd);

#endif
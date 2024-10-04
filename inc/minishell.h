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
#include <stdbool.h> // bool -- we could use bitwise too







#include <libft/libft.h> // libft



#endif
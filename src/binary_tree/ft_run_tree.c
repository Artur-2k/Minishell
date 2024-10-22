#include "minishell.h"


char *ft_check_paths_for_cmd(char **paths, char *cmd)
{
    char *full_path;
    int j = 0;
    while (paths[j] != NULL)
    {
        paths[j] = ft_append_char_to_str(paths[j], '/');
        full_path = ft_strjoin(paths[j], cmd);
        if (access(full_path, X_OK) == 0)
            break ;
        free(full_path); // comando errado freed
        full_path = NULL;
        j++;
    }
    return full_path;
}
void    ft_exec(t_exec *node)
{
    char *full_path;
    char *path_var;
    char    **paths;

    printf("pipipopu\n");
    printf("pipipopu\n");

    if (access(node->av[0], X_OK) != 0)
    {
        path_var = ft_get_value("PATH", node->envp);
        //todo (if !path_var)...
        paths = ft_split(path_var, ':');
        //todo (if !paths)...
        full_path = ft_check_paths_for_cmd(paths, node->av[0]);
        if (!full_path)
        {
            ft_putstr_fd(node->av[0], 2);
            ft_putstr_fd(": command not found\n", 2);
            //todo ver mais error handling
        }
        else
            execve(full_path, node->av, NULL);
    }
    else
    {
        if (execve(node->av[0], node->av, NULL))
        {
            ft_putstr_fd(node->av[0], 2);
            ft_putstr_fd(": command not found\n", 2);
        }
    }
  
    if (node->redir_list) // todo
    {}

}

void ft_run_tree(t_cmd *node)
{
    t_pipe  *npipe;
    int     fd[2];

    if (node->type == EXEC)
    {
        ft_exec((t_exec *)node);
        //todo error
        exit (1);
    }
    else if (node->type == PIPE)
    {
        npipe = (t_pipe *)node;
        if (pipe(fd) < 0) // todo
            exit (1);

        if (fork() == 0)
        {
            close(1);
            dup(fd[WRITE_END]);
            close(fd[WRITE_END]);
            close(fd[READ_END]);
            ft_run_tree((t_cmd *)npipe->left);
            exit (1);
        }
        if (fork() == 0)
        {
            close(0);
            dup(fd[READ_END]);
            close(fd[WRITE_END]);
            close(fd[READ_END]);
            ft_run_tree((t_cmd *)npipe->right);
            exit (1);
        }
        close(fd[WRITE_END]);
        close(fd[READ_END]);
        wait (0);
        wait (0);
        exit (0);
    }
    return ;
}
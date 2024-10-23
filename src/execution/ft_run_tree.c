#include "minishell.h"

void    ft_exec(t_exec *node)
{
    char *full_path;
    char *path_var;
    char    **paths;
    char    **envp;

    if (node->envp)
        envp = ft_recreate_envp(node->envp);

    if (node->redir_list) // TODO
    {
        if (ft_redirects(node->redir_list))
        {exit (1);} // TODO ERROR CHECK
    }

    // check if it is a dir
    struct stat file_stat;
    /*
     *   st_size: Tamanho do arquivo em bytes.
     *   st_mode: Define o tipo do arquivo e as permissões.
     *   st_nlink: Número de links para o arquivo (quantas referências existem para o mesmo inode).
     *   st_uid: ID do proprietário do arquivo.
     *   st_gid: ID do grupo ao qual o arquivo pertence.
     *   st_atime: Último acesso ao arquivo (timestamp).
     *   st_mtime: Última modificação no conteúdo do arquivo (timestamp).
     *   st_ctime: Última modificação no status (metadados) do arquivo (timestamp).
     *
     *  Macros de modos para tipo de arquivo...
     *  S_ISREG(m): Verifica se o arquivo é regular.
     *  S_ISDIR(m): Verifica se é um diretório.
    */
    stat(node->av[0], &file_stat);
    // so reconhece diretorios quando tem uma / e quando e diretorio
    if (ft_strchr(node->av[0], '/') && S_ISDIR(file_stat.st_mode))
    {
        ft_putstr_fd(node->av[0], 2);
        ft_putstr_fd(": is a directory sir\n", 2);
        exit (1);
    }


    //* strchr(.. /) tendo execve n tendo paths
    if (ft_strchr(node->av[0], '/')) // path absoluto ==> execve
    {
        if (access(node->av[0], X_OK) == 0)
        {
            execve(node->av[0], node->av, envp);
            // TODO ERROR CHECK
        }
        else // bin doesnt exist, no permission
        {
            // TODO ERROR CHECK
            printf("ERRO MALANDRO1\n");
            exit (1);
        }
    }
    else // find path
    {
        path_var = ft_get_value("PATH", node->envp);
        if (!path_var || !*path_var) // ==>execve
        {
            if (access(node->av[0], X_OK) == 0)
            {
                execve(node->av[0], node->av, envp);
                // TODO ERROR CHECK
            }
            else // bin doesnt exist, no permission
            {
                // TODO ERROR CHECK
                printf("ERRO MALANDRO2\n");
                exit (1);
            }
        }
        else
        {
            paths = ft_split(path_var, ':');
            //todo (if !paths)...
            free(path_var);
            full_path = ft_check_paths_for_cmd(paths, node->av[0]);
            ft_free_str_arr(paths);
            if (!full_path)
            {
                ft_putstr_fd(node->av[0], 2);
                ft_putstr_fd(": command not found\n", 2);
                //todo ver mais error handling
                exit (1);
            }
            else
            {
                free(node->av[0]);
                node->av[0] = ft_strdup(full_path);
                execve(node->av[0], node->av, envp);
                free(full_path);
            }
        }
    }
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

        int pid = fork();
        if (pid == 0)
        {
            close(1);
            dup(fd[WRITE_END]);
            close(fd[WRITE_END]);
            close(fd[READ_END]);
            ft_run_tree((t_cmd *)npipe->left);
            exit (1);
        }
        int pid2 = fork();
        if (pid2 == 0)
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

#include "minishell.h"


int ft_is_dir(char *path)
{
    if (!path) // TODO
        exit(2);
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
    // so reconhece diretorios quando tem uma / e quando e diretorio
    if (ft_strchr(path, '/'))
    {
        errno = 0;
        if (stat(path, &file_stat))
        {
            printf("error1\t");
            ft_what_happened(path, strerror(errno));
            exit (1); // TODO
        }
        if (S_ISDIR(file_stat.st_mode))
        {
            printf("error2\t");

            ft_what_happened(path, ": Is a directory");
            exit (126); // TODO
        }   
    }
    return (0); // success
}

/* char    *ft_get_cmd_path(char *cmd, char **envp)
{
  


    return 
} */

void    ft_exec(t_exec *node)
{

  char    *full_path;
    char    *path_var;
    char    **paths;
    // apply redirects
    if (ft_redirects(node->redir_list))
        {exit (1);} // TODO ERROR CHECK

    // check if it is a dir
    if (ft_is_dir(node->av[0]))
        {exit(1);} // TODO ERROR CHECK

    //* strchr(.. /) tendo execve n tendo paths



    if (ft_strchr(node->av[0], '/')) // path absoluto ==> execve
    {
        errno = 0;
        if (access(node->av[0], X_OK) == 0)
        {
            errno = 0;
            execve(node->av[0], node->av, node->tenvp);
        }
        ft_what_happened(node->av[0], strerror(errno));
        exit (1); // TODO ERROR CHECK
    }
    else // find path
    {
        path_var = ft_get_value("PATH", node->envp);
        if (!path_var || !*path_var) // ==>execve
            ft_what_happened(node->av[0], ": No such file or directory");
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
                execve(node->av[0], node->av, node->tenvp);
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

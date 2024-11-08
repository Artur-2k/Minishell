/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 12:33:23 by artuda-s          #+#    #+#             */
/*   Updated: 2024/11/08 18:18:12 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	ft_is_dir(char *path)
{
    struct stat	file_stat;

    // so reconhece diretorios se o path tiver uma barra no fim */
    if (ft_strchr(path, '/'))
    {
        errno = 0;
        if (stat(path, &file_stat))
        {
            ft_what_happened(path, strerror(errno));
        	return (EXIT_404);
        }
        if (S_ISREG(file_stat.st_mode))
        {
            if (access(path, X_OK) != 0)
            {
                ft_what_happened(path, strerror(errno));
                return (EXIT_FNOK);
            }
        }
        if (S_ISDIR(file_stat.st_mode))
        {
            ft_what_happened(path, ": Is a directory");
            return (EXIT_FNOK);
        }
    }
    return (EXIT_SUCCESS); // Not a dir and path exists
}

static char    *ft_get_cmd_path(char *cmd, t_envp *envp)
{
	char    *full_path;
    char    *path_var;
    char    **paths;

	path_var = ft_get_value("PATH", envp);
	if (!path_var)
		return (ft_what_happened(cmd, "command not found"), NULL);
    paths = ft_split(path_var, ':');
	if (!paths)
		return (ft_putstr_fd("Malloc error, sir\n", 2), NULL);
    full_path = ft_check_paths_for_cmd(paths, cmd);
    ft_free_str_arr(paths);
	if (!full_path)
		return (ft_what_happened(cmd, "command not found"), NULL);
    return (full_path);
}

static int	ft_exec_path(t_exec *ecmd)
{
	errno = 0;

	if (access(ecmd->av[0], X_OK) != 0)
    {
        ft_what_happened(ecmd->av[0], strerror(errno));
        return (EXIT_FNOK);
    }
    errno = 0;
    execve(ecmd->av[0], ecmd->av, ecmd->tenvp);
    ft_what_happened(ecmd->av[0], strerror(errno));
    return (EXIT_FAILURE); // error
}

static int	ft_exec_no_path(t_exec *ecmd)
{
	char	*cmd;

	cmd = ft_get_cmd_path(ecmd->av[0], ecmd->envp);
	if (!cmd)
		return (EXIT_404); // error
    execve(cmd, ecmd->av, ecmd->tenvp);
	ft_what_happened(ecmd->av[0], strerror(errno));
	return (EXIT_FAILURE); // error
}

int    ft_exec(t_exec *node)
{
    int error;

	if (node->av[0] == NULL) // $a
		return (0);
	if (node->av[0][0] == '\0') // "" || ''
	{
		ft_putstr_fd("Command '' not found, sir\n", 2);
		return (EXIT_404);
	}


    // check if it is a dir
    error = 0;
    error = ft_is_dir(node->av[0]);
    if (error)
		return (error);



    // apply redirects
    error = ft_redirects(node->redir_list);
    if (error)
		return (error);

	if (ft_is_builtin(node))
	{
		ft_redirect_execution(node);
		return (node->shell->exit_status);
	}

    //* strchr(.. /) tendo execve n tendo paths
    if (ft_strchr(node->av[0], '/')) // path absoluto ==> execve
	{
        error = ft_exec_path(node);
		if (ft_exec_path(node))
			return (EXIT_404);
	}
    else // find path (access on getcmdpath)
	{
        error = ft_exec_no_path(node);
		if (error)
            return (error);
	}
	return (EXIT_FAILURE);
}

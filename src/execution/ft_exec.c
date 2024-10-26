/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 12:33:23 by artuda-s          #+#    #+#             */
/*   Updated: 2024/10/26 13:22:30 by artuda-s         ###   ########.fr       */
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

	if (!path) // TODO
        exit(2);
    // so reconhece diretorios se o path tiver uma barra no fim */
    if (ft_strchr(path, '/'))
    {
        errno = 0;
        if (stat(path, &file_stat))
        {
            ft_what_happened(path, strerror(errno));
            exit (1); // TODO
        }
        if (S_ISDIR(file_stat.st_mode))
        {
            ft_what_happened(path, ": Is a directory");
            exit (126); // TODO
        }
    }
    return (0); // Not a dir
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
    free(path_var);
    full_path = ft_check_paths_for_cmd(paths, cmd);
    ft_free_str_arr(paths);
	if (!full_path)
		return (ft_what_happened(cmd, "command not found"), NULL);
    return (full_path);
}

static int	ft_exec_path(t_exec *ecmd)
{
	errno = 0;
	if (access(ecmd->av[0], X_OK) == 0)
    {
        errno = 0;
        execve(ecmd->av[0], ecmd->av, ecmd->tenvp);
    }
    ft_what_happened(ecmd->av[0], strerror(errno));
    return (1); // error
}

static int	ft_exec_no_path(t_exec *ecmd)
{
	char	*cmd;

	cmd = ft_get_cmd_path(ecmd->av[0], ecmd->envp);
	if (!cmd)
		exit(1); //TODO
   	free(ecmd->av[0]);
    ecmd->av[0] = ft_strdup(cmd);
    execve(ecmd->av[0], ecmd->av, ecmd->tenvp);
	ft_what_happened(ecmd->av[0], strerror(errno));
	return (1); // error
}

int    ft_exec(t_exec *node)
{
    // apply redirects
    if (ft_redirects(node->redir_list))
        {exit (1);} // TODO ERROR CHECK

    // check if it is a dir
    if (ft_is_dir(node->av[0]))
        {exit(1);} // TODO ERROR CHECK

    //* strchr(.. /) tendo execve n tendo paths
    if (ft_strchr(node->av[0], '/')) // path absoluto ==> execve
	{
		if (ft_exec_path(node))
				exit (1); //TODO
	}
    else // find path (access on getcmdpath)
		if (ft_exec_no_path(node))
			exit (1); //TODO
	return (0); // TODO
}
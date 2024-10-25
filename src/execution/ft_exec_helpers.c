/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:15:50 by artuda-s          #+#    #+#             */
/*   Updated: 2024/10/25 20:03:06 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    **ft_recreate_envp(t_envp *l_envp)
{
    char    **envp;
    t_envp  *backup;
    int     len;

    backup = l_envp;
    len = 0;
    while (l_envp && ++len) //! short circuiting for lines WATCH OUT
        l_envp = l_envp->next;
    l_envp = backup;
    envp = (char **)malloc(sizeof(char *) * (len + 1));
    if (!envp)
        return (NULL);
    len = 0;
    while (l_envp)
    {
        envp[len] = ft_strappend(ft_strjoin(l_envp->key, "="), l_envp->value); //! WATCH OUT FOR NULL PARAMS
        if (!envp[len])
            return (ft_free_str_arr(envp), NULL);
        len++;
        l_envp = l_envp->next;
    }
    envp[len] = NULL;
    return (envp);
}

char *ft_check_paths_for_cmd(char **paths, char *cmd)
{
    char	*full_path;
	int		i;

    i = 0;
    while (paths[i] != NULL)
    {
		full_path = ft_strjoin(paths[i], "/");
		if (!full_path)
			return (NULL);
        full_path = ft_strappend(full_path, cmd);
        if (access(full_path, X_OK) == 0)
            break ;
        free(full_path); // comando errado freed
        full_path = NULL;
        i++;
    }
    return (full_path);
}

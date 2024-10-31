/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:15:50 by artuda-s          #+#    #+#             */
/*   Updated: 2024/10/31 14:26:50 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char    *ft_check_paths_for_cmd(char **paths, char *cmd)
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
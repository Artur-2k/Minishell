/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:15:50 by artuda-s          #+#    #+#             */
/*   Updated: 2024/11/11 22:21:53 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Loops around the contents of the paths string array and looks for
 * a match that can be executable (X_OK) and returns it if found.
 * @return	Returns NULL if not found, and the full path if one is executable
 */
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
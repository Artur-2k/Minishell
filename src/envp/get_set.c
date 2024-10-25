/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:30:00 by artuda-s          #+#    #+#             */
/*   Updated: 2024/10/25 19:48:38 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_has_key(char *try, int len,  t_envp *envp)
{
	if (!*try || !try || !envp)
		return (false);
	while (envp != NULL)
	{
		if (!ft_strncmp(try, envp->key, len))
			return (true);
		envp = envp->next;
	}
	return (false);
}

char *ft_get_value(char *key, t_envp *envp)
{
	if (!key || !*key || !envp)
		return (NULL);

	while (envp != NULL)
	{
		if (!ft_strcmp(key, envp->key))
			return (envp->value);
		envp =envp->next;
	}
	return ("");
}



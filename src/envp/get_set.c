/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:30:00 by artuda-s          #+#    #+#             */
/*   Updated: 2024/11/11 17:14:15 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_has_key(char *try,  t_envp *envp)
{
	if (!try || !*try || !envp)
		return (false);
	while (envp != NULL)
	{
		if (!ft_strcmp(try, envp->key))
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

//TODO error checking
void	ft_set_value(char *key, char *value, t_envp *envp)
{
	t_envp *cur;

	if (!key || !*key || !value)
		return ;
	if (!envp)
		envp = ft_new_env_node(key, value);
	cur = envp;
	while (cur)
	{
		if (ft_strcmp(key, cur->key) == 0)
		{
			free(cur->value);
			cur->value = ft_strdup(value);
			return ;
		}
		cur = cur->next;
	}
	cur = envp;
	while (cur->next)
		cur = cur->next;
	cur->next = ft_new_env_node(key, value);
	return ;
}

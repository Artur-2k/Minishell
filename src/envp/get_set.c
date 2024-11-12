/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:30:00 by artuda-s          #+#    #+#             */
/*   Updated: 2024/11/12 21:42:59 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Checks for a match of the key on envp
 * @return	Returns true if there is one or false if not
 */
bool	ft_has_key(char *try, int len,  t_envp *envp)
{
	if (!try || !*try || !envp)
		return (false);
	while (envp != NULL)
	{
		if (!ft_strncmp(try, envp->key, len))
			return (true);
		envp = envp->next;
	}
	return (false);
}



/**
 * @brief	Will look for a match for the key on the envp list
 * @return	Returns A POINTER to the corresponding value or an EMPTY STRING
 * if no match is found
*/
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

/**
 * @brief	Will look for the key on envp and replace its contents with a copy of the
 * value passed as a parameter. If there is no list create one node to it
 * @param key The key to look for
 * @param value The value to replace with
 * @param envp The env
 */
void	ft_set_value(char *key, char *value, t_envp *envp)
{
	t_envp *cur;

	if (!key || !*key || !value)
		return ;

	if (!envp)
		envp = ft_new_env_node(key, value); // check malloc

	cur = envp;
	while (cur)
	{
		if (ft_strcmp(key, cur->key) == 0)
		{
			free(cur->value);
			cur->value = ft_strdup(value); // check malloc
			return ;
		}
		cur = cur->next;
	}
	cur = envp;
	while (cur->next)
		cur = cur->next;
	cur->next = ft_new_env_node(key, value); // check malloc
	return ;
}

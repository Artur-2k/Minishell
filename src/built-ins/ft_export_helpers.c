/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 22:30:20 by artuda-s          #+#    #+#             */
/*   Updated: 2024/12/16 10:25:47 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define ENV1    1
#define ENV2    2
#define REPLACE 3
#define APPEND  4

static int	ft_check_replace(char *try, t_envp *envp)
{
	if (!try || !*try || !envp)
		return (false);
	while (envp != NULL)
	{
		if (!strcmp(try, envp->key))
			return (true);
		envp = envp->next;
	}
	return (false);
}

static int	ft_replace_value(t_envp **head, char *key, char *value, int mode)
{
	t_envp	*cur;

	cur = *head;
	while (ft_strcmp(key, cur->key) != 0)
		cur = cur->next;
	if (value && mode == REPLACE)
	{
		if (cur->value)
			free(cur->value);
		cur->value = ft_strdup(value);
		if (!cur->value)
			return (1);
	}
	else
	{
		cur->value = ft_strappend(cur->value, value);
		if (!cur->value)
			return (1);
	}
	return (0);
}

int	ft_add_entry_env(t_envp **head, char *key, char *value, int mode)
{
	t_envp	*temp;

	if (ft_check_replace(key, *head))
		ft_replace_value(head, key, value, mode);
	else
	{
		if (*head == NULL)
		{
			*head = ft_new_env_node(key, value);
			if (!*head)
				return (1);
		}
		else
		{
			temp = *head;
			while (temp->next != NULL)
				temp = temp->next;
			temp->next = ft_new_env_node(key, value);
			if (!temp->next)
				return (2);
		}
	}
	return (0);
}

int	ft_add_entry_env2(t_envp **head, char *key, char *value, int mode)
{
	t_envp	*new;
	t_envp	*cur;

	if (ft_check_replace(key, *head))
		ft_replace_value(head, key, value, mode);
	else
	{
		new = ft_new_env_node(key, value);
		if (!new)
			return (1);
		if (*head == NULL || ft_strcmp((*head)->key, key) > 0)
		{
			new->next = *head;
			*head = new;
			return (0);
		}
		cur = *head;
		while (cur->next != NULL && ft_strcmp(cur->next->key, new->key) < 0)
			cur = cur->next;
		new->next = cur->next;
		cur->next = new;
	}
	return (0);
}

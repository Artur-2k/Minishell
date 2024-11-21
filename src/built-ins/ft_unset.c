/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 21:32:33 by artuda-s          #+#    #+#             */
/*   Updated: 2024/11/21 14:17:10 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * unset     - return
 *
 * unset lixo	checka se tem e se nao tem passa para o proximo arg ate null
 *
 * e se tiver remove
 *
 * unset a b c
 *
 * checa se tem a b e c e se tiver remove
 *
*/

void	ft_delete_node(char *key, t_envp **head)
{
	t_envp	*cur;
	t_envp	*prev;

	cur = *head;
	prev = NULL;
	while (cur != NULL)
	{
		if (ft_strcmp(key, cur->key) == 0)
		{
			if (prev == NULL)
				*head = cur->next;
			else
				prev->next = cur->next;
			free(cur->key);
			free(cur->value);
			free(cur);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}

void	ft_unset(t_exec *cmd)
{
	int	i;

	cmd->shell->exit_status = 0;
	if (!cmd->av[1])
		return ;
	i = 1;
	while (cmd->av[i])
	{
		if (ft_has_key(cmd->av[i], ft_strlen(cmd->av[i]), \
		cmd->shell->my_envp_h))
			ft_delete_node(cmd->av[i], &cmd->shell->my_envp_h);
		if (ft_has_key(cmd->av[i], ft_strlen(cmd->av[i]), \
		cmd->shell->envp2lol_h))
			ft_delete_node(cmd->av[i], &cmd->shell->envp2lol_h);
		i++;
	}
}

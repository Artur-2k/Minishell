/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 21:32:33 by artuda-s          #+#    #+#             */
/*   Updated: 2024/11/12 22:02:03 by artuda-s         ###   ########.fr       */
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


void ft_delete_node(char *key, t_envp **head)
{
    t_envp *cur = *head;
    t_envp *prev = NULL;

    while (cur != NULL)
    {
        if (ft_strcmp(key, cur->key) == 0)
        {
            if (prev == NULL)
                *head = cur->next; // Deleting the first node
            else
                prev->next = cur->next; // Deleting a middle or last node

            free(cur->key);
            free(cur->value);
            free(cur);
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}


void	ft_unset(t_exec *cmd)
{
	cmd->shell->exit_status = 0;
	if (!cmd->av[1])
		return ;

	int i = 1;
	while (cmd->av[i])
	{
		// env list
		if (ft_has_key(cmd->av[i], ft_strlen(cmd->av[i]), cmd->shell->my_envp_h))
			ft_delete_node(cmd->av[i], &cmd->shell->my_envp_h);

		// export list
		if (ft_has_key(cmd->av[i], ft_strlen(cmd->av[i]), cmd->shell->envp2lol_h))
			ft_delete_node(cmd->av[i], &cmd->shell->envp2lol_h);

		i++;
	}
}

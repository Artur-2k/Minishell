/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_frees.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:29:51 by artuda-s          #+#    #+#             */
/*   Updated: 2024/10/26 21:53:05 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_free_str_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void ft_free_envp_lst(t_envp *my_envp)
{
    t_envp  *temp;

    while (my_envp != NULL)
    {
        temp = my_envp->next;
        free(my_envp->value);
        free(my_envp->key);
        free(my_envp);
        my_envp = temp;
    }
}

void    ft_free_redir_list(t_redir **redirs)
{
    t_redir *temp;

    while (*redirs != NULL)
    {
        free((*redirs)->redir);
        temp = (*redirs)->next;
        free(*redirs);
        *redirs = temp;
    }
}

void    ft_free_tree(t_cmd *tree)
{
    t_exec  *execn;
    t_pipe  *pipen;
    if (tree->type == EXEC)
    {
        execn = (t_exec *)tree;
        ft_free_str_arr(execn->av);
        ft_free_str_arr(execn->tenvp);
        ft_free_redir_list(&execn->redir_list);
        free(execn);
    }
    else if (tree->type == PIPE)
    {
        pipen = (t_pipe *)tree;
        ft_free_tree((t_cmd *)pipen->left);
        ft_free_tree((t_cmd *)pipen->right);
        free(pipen);
    }
}

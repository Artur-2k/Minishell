/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_frees.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:29:51 by artuda-s          #+#    #+#             */
/*   Updated: 2024/10/31 15:58:01 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tokens(t_tokens **tokens)
{
	int i = 0;
	while (tokens[i])
	{
	    if (tokens[i]->token)
		    free(tokens[i]->token);
	    if (tokens[i])
            free(tokens[i]);
		i++;
	}
    if (tokens)
        free(tokens);

    return ;
}


void ft_free_str_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
        if (arr[i])
            free(arr[i]);

        i++;
	}
    if (arr)
    	free(arr);
}

void ft_free_envp_lst(t_envp *my_envp)
{
    t_envp  *temp;

    while (my_envp != NULL)
    {
        temp = my_envp->next;
        if (my_envp->value)
            free(my_envp->value);
        if (my_envp->key)
            free(my_envp->key);
        if (my_envp)
            free(my_envp);
        my_envp = temp;
    }
}

void    ft_free_redir_list(t_redir **redirs)
{
    t_redir *temp;

    while (*redirs != NULL)
    {
        if ((*redirs)->redir)
            free((*redirs)->redir);
        temp = (*redirs)->next;
        if (*redirs)
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
        if (execn)
            free(execn);
    }
    else if (tree->type == PIPE)
    {
        pipen = (t_pipe *)tree;
        ft_free_tree((t_cmd *)pipen->left);
        ft_free_tree((t_cmd *)pipen->right);
        if (pipen)
            free(pipen);
    }
}

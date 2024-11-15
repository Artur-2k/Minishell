/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_frees.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelo-ca <dmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:29:51 by artuda-s          #+#    #+#             */
/*   Updated: 2024/11/15 13:11:33 by dmelo-ca         ###   ########.fr       */
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
	while (arr && arr[i] != NULL)
	{
        if (arr[i])
            free(arr[i]);

        i++;
	}
    if (arr)
    	free(arr);
}

void ft_free_envp_lst(t_envp *cur)
{
    t_envp  *temp;

    while (cur != NULL)
    {
        temp = cur->next;
        if (cur->value)
            free(cur->value);
        if (cur->key)
            free(cur->key);
        if (cur)
            free(cur);
        cur = temp;
    }
}

void    ft_free_redir_list(t_redir **redirs)
{
    t_redir *temp;

    while (redirs && *redirs != NULL)
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

//TODO FREE THE HEREDOC PATHS

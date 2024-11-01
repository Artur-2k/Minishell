/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 19:27:57 by artuda-s          #+#    #+#             */
/*   Updated: 2024/11/01 17:45:31 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*
 * 
 *
 *
*/
void ft_run_tree(t_cmd *node, t_shell *shell)
{
	int	exit_status;

	exit_status = 1;
    if (node->type == EXEC)
    {
        exit_status = ft_exec((t_exec *)node); 
        //todo error
    }
    else if (node->type == PIPE)
    {
		ft_pipe((t_pipe *)node, shell);
		// free all
    }

	free(shell->input);
	ft_free_tree(shell->cmd_tree);
    ft_free_envp_lst(shell->my_envp_h);
    rl_clear_history();
	exit (exit_status);
}

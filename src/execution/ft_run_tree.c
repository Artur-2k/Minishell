/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 19:27:57 by artuda-s          #+#    #+#             */
/*   Updated: 2024/11/07 16:37:59 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*
 * @brief This function is the root of the execution and will be called 
 * recursively. This function doens't return but exits only in case of error
 * or on execve
*/
void ft_run_tree(t_cmd *node, t_shell *shell)
{
    if (node->type == EXEC)
	{
		ft_signal_restore();
        shell->exit_status = ft_exec((t_exec *)node); 
	}
    else if (node->type == PIPE)
	{
		ft_pipe((t_pipe *)node, shell);
		
	}

	// Free everything
	free(shell->input);
	free(shell->spid);
    free(shell->sexit_status);
	ft_free_tree(shell->cmd_tree);
    ft_free_envp_lst(shell->my_envp_h);
	ft_free_envp_lst(shell->envp2lol_h); // envp list
    rl_clear_history();
	
	exit (shell->exit_status);
}

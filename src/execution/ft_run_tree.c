/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 19:27:57 by artuda-s          #+#    #+#             */
/*   Updated: 2024/10/26 13:23:08 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void ft_run_tree(t_cmd *node, t_shell *shell)
{
	int	exit_status;

	exit_status = 0;
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

	exit (exit_status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_everything.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelo-ca <dmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 19:09:25 by artuda-s          #+#    #+#             */
/*   Updated: 2024/11/21 14:45:39 by dmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Initializes envp and a copy for export and silences warnings from
 * flags on ac and av. Also inits some variables to be used later
 * @retval	Returns 0 on success and non-zero on error
*/
int	ft_init_everything(t_shell *shell, char *envp[], int ac, char **av)
{
	(void)ac;
	(void)av;
	ft_config_terminal();
	ft_init_signals();
	if (ft_init_envp(shell, envp))
		return (1);
	if (ft_init_envp2lol(shell, envp))
		return (2);
	shell->cmd_tree = NULL;
	shell->status = 0;
	shell->exit_status = 0;
	shell->sexit_status = ft_strdup("0");
	shell->pid = ft_get_pid();
	shell->spid = ft_itoa(shell->pid);
	if (!shell->spid || !shell->sexit_status)
		return (3);
	return (0);
}

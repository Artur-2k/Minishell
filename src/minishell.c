/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:33:37 by artuda-s          #+#    #+#             */
/*   Updated: 2024/11/21 14:55:02 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern unsigned char	g_signal;

static void	ft_norminnete(t_shell *shell)
{
	while (true)
	{
		g_signal = 0;
		shell->input = readline(RED"Minihell => "RES);
		if (shell->input == NULL)
			break ;
		if (g_signal)
		{
			shell->exit_status = 128 + g_signal;
			free(shell->sexit_status);
			shell->sexit_status = ft_itoa(shell->exit_status);
		}
		if (ft_tokenizer(shell))
		{
			add_history(shell->input);
			shell->exit_status = 1;
			free(shell->input);
			continue ;
		}
		ft_run_cmd(shell);
		if (*shell->input != '\0')
			add_history(shell->input);
		free(shell->input);
	}
}

int	main(int ac, char **av, char *envp[])
{
	t_shell	shell;

	if (ft_init_everything(&shell, envp, ac, av))
		return (ft_putstr_fd("Malloc error, sir\n", STDERR_FILENO), 1);
	ft_norminnete(&shell);
	free(shell.spid);
	free(shell.sexit_status);
	ft_free_envp_lst(shell.envp2lol_h);
	ft_free_envp_lst(shell.my_envp_h);
	rl_clear_history();
	printf("exit\n");
	return (0);
}

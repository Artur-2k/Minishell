/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:42:45 by artuda-s          #+#    #+#             */
/*   Updated: 2024/11/11 21:05:26 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	We will check if the program exited normally or was signaled
 * and act accordingly.
 * Sig quit core dumps and sig int writes a new line
 */
static void	ft_fetch_exit_status(t_shell *shell)
{
	if (WIFEXITED(shell->status))
        shell->exit_status = WEXITSTATUS(shell->status);
    else if (WIFSIGNALED(shell->status))
    {
        int signo;
        signo = WTERMSIG(shell->status);
        if (signo == SIGINT)
            ft_putstr_fd("\n", 2);
        else if (signo == SIGQUIT)
            ft_putstr_fd("Quit (core dumped), sir\n", 2);
        shell->exit_status = 128 + signo;
    }
}

/**
 * @brief	If the command is a simple built in without pipe it must be ran
 * on the main process so changes can take places (chdir, export and stuff).
 * Main proccess should ignore signals while child processes should restore
 * default function. We fork and do the execution on a child process and then
 * fetch the exit status of that child
 */
void    ft_run_cmd(t_shell *shell)
{
    int	pid;

    if (!shell->cmd_tree)
		return ;

	// If there is only a built in it must be ran on main process
	if (shell->cmd_tree->type == EXEC &&
		ft_is_builtin(shell->cmd_tree))
		ft_run_builtin((t_exec *)shell->cmd_tree);
	else
	{
		// Mute signals from parent
	    ft_signal_ignore();

	    // Child doenst return back here it exits
		pid = fork();
	    if (pid == 0)
	        ft_run_tree(shell->cmd_tree, shell);

		// Exit status
	    waitpid(pid, &shell->status, 0);
		ft_fetch_exit_status(shell);

		// Restore signals
		ft_init_signals();
	}
    // Replace exit status
    free(shell->sexit_status);
    shell->sexit_status = ft_itoa(shell->exit_status);

    ft_free_tree(shell->cmd_tree);
    shell->cmd_tree = NULL;
}

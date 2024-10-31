/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:33:37 by artuda-s          #+#    #+#             */
/*   Updated: 2024/10/31 10:32:16 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Global for signal
extern unsigned char	g_signal_pressed;

int     main(int ac, char** av, char *envp[])
{
    t_shell    shell;

    // dont know if needed but for Wflags
    (void)ac;
    (void)av;

    // probably init shell bools and shit
    ft_init_signals(&shell);
    if (ft_init_envp(&shell, envp))
		return (ft_putstr_fd("Malloc error, sir\n", STDERR_FILENO), 1);
    shell.cmd_tree = NULL;
    while (true)
    {
		g_signal_pressed = 0;

		// Reads input from user
        shell.input = readline(RED"Minihell => "RES);

		if (g_signal_pressed)
			shell.exit_status = g_signal_pressed;
        // Ctrl+D (EOF), readline retorna NULL
        if (shell.input == NULL)
            break;

        // Tokenizes the input and checks for syntax errors
        ft_tokenizer(&shell); // TODO error checking a partir daqui is missing

        if (shell.cmd_tree)
        {
            int	status;
			int	pid;

			pid = fork();
            if (pid == 0)
                ft_run_tree(shell.cmd_tree, &shell);
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				shell.exit_status = WEXITSTATUS(status);
			else if (WTERMSIG(status)){} //TODO signal e tal

            ft_free_tree(shell.cmd_tree);
			shell.cmd_tree = NULL;
        }

        // Verifica se o input não está vazio antes de adicionar ao histórico
	    if (*shell.input != '\0')
            add_history(shell.input);

        free(shell.input);
    }

    //release everything
    // envp, tree (! pais e filhos)
    ft_free_envp_lst(shell.my_envp_h);
    rl_clear_history();
    printf("exit\n");
    return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelo-ca <dmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:33:37 by artuda-s          #+#    #+#             */
/*   Updated: 2024/11/20 15:20:15 by dmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern unsigned char g_signal;

int     main(int ac, char** av, char *envp[])
{
    t_shell    shell;

	// Initializing everything
	if (ft_init_everything(&shell, envp, ac, av))
		return (ft_putstr_fd("Malloc error, sir\n", STDERR_FILENO), 1);

	// Read -> Parse -> Execute -> Repeat
    while (true)
    {
        // Ctrl C
        g_signal = 0;

		// Reads input from user
        shell.input = readline(RED"Minihell => "RES);

        // Ctrl+D (EOF), readline retorna NULL
        if (shell.input == NULL)
            break;

        if (g_signal)
        {
            shell.exit_status = 128 + g_signal;
            free(shell.sexit_status);
            shell.sexit_status = ft_itoa(shell.exit_status);
        }


        // Tokenizes the input and checks for syntax errors
        if (ft_tokenizer(&shell))
        {
            add_history(shell.input);
            shell.exit_status = 1;
            free(shell.input);
            continue ;
        }

        // This function doesnt need a return statement
        ft_run_cmd(&shell);

        // Verifica se o input não está vazio antes de adicionar ao histórico
	    if (*shell.input != '\0')
            add_history(shell.input);

        free(shell.input); // input
    }

    //release everything
    // envp, tree , history
    free (shell.spid);
    free (shell.sexit_status);
    ft_free_envp_lst(shell.envp2lol_h); // envp list
    ft_free_envp_lst(shell.my_envp_h); // envp list
    rl_clear_history(); // history
    printf("exit\n");
    return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:33:37 by artuda-s          #+#    #+#             */
/*   Updated: 2024/10/24 10:00:00 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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
		// Reads input from user
        shell.input = readline(RED"Minihell => "RES);

        // Ctrl+D (EOF), readline retorna NULL
        if (shell.input == NULL)
            break;

        // Tokenizes the input and checks for syntax errors
        ft_tokenizer(&shell); // TODO error checking a partir daqui is missing

        if (shell.cmd_tree)
        {
            int pid = fork();
            if (pid == 0)
                ft_run_tree(shell.cmd_tree);
            wait (NULL);
        }

        // Verifica se o input não está vazio antes de adicionar ao histórico
        if (*shell.input != '\0')
            add_history(shell.input);

        free(shell.input);
    }

    //release everything
    // envp, tree (! pais e filhos)
    printf("exit\n");
    return (0);
}

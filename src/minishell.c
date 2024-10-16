/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:33:37 by artuda-s          #+#    #+#             */
/*   Updated: 2024/10/16 14:25:11 by artuda-s         ###   ########.fr       */
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
    ft_init_envp(&shell, envp); //todo

    while (true)
    {
        shell.input = readline("\033[0;31mMinihell => \033[0m");
        // Ctrl+D (EOF), readline retorna NULL
        if (shell.input == NULL)
            break;

        // tokenizes the input and checks for syntax errors
        ft_tokenizer(&shell);


        // Verifica se o input não está vazio antes de adicionar ao histórico
        if (*shell.input != '\0')
            add_history(shell.input);

        free(shell.input);
    }

    //release everything

    printf("exit\n");
    return (0);
}

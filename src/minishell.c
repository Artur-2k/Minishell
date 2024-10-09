/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:33:37 by artuda-s          #+#    #+#             */
/*   Updated: 2024/10/09 18:50:42 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     main(int ac, char** av, char *envp[])
{
    t_shell    shell;

    // dont know if needed but for flags
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
        
        ft_tokenizer(&shell);
        

        // Verifica se o input não está vazio antes de adicionar ao histórico
        if (*shell.input != '\0') 
            add_history(shell.input);
        free(shell.input);
    }
    
    //release everything

    printf("\nexit");
    return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:33:37 by artuda-s          #+#    #+#             */
/*   Updated: 2024/10/04 16:24:57 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_tokenizer(t_sh *shell)
{
    
}

int main(void)
{
    t_sh    shell;

    // probably init shell bools and shit
    ft_init_signals(&shell);
    
    while (true)
    {
        shell.input = readline("Minishell");
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

    printf("\nexit\n");
    return (0);
}

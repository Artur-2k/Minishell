/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:33:37 by artuda-s          #+#    #+#             */
/*   Updated: 2024/10/09 14:13:14 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 redirs 
    command > file
    command < FILE
    command >> FILE
    command << STRING_TO_BE_FOUND
pipe
    command | command
0 ou mais espacos 


Comando
    comando -flag       args
0 ou mais espacos. Nunca junto


  cat <infile |grep    texto >file.txt
 */  

 void    ft_tokenizer(t_shell *shell)
{
    char    *in = shell->input;
    if (!in || !*in)
        return ;
    
    
    
    
}


int main(void)
{
    t_shell    shell;

    // probably init shell bools and shit
    ft_init_signals(&shell);
    
    
    while (true)
    {
        shell.input = readline("$Minishell>");
        // Ctrl+D (EOF), readline retorna NULL
        if (shell.input == NULL)
            break;
        
        //ft_tokenizer(&shell);
        

        // Verifica se o input não está vazio antes de adicionar ao histórico
        if (*shell.input != '\0') 
            add_history(shell.input);
        free(shell.input);
    }
    
    //release everything

    printf("\nexit");
    return (0);
}

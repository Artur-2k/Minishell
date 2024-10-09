/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:50:16 by artuda-s          #+#    #+#             */
/*   Updated: 2024/10/09 18:00:48 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO 🗹
//! add a struct for shell to point to
//! free the array

//* read into an array of tokens 🗹
//! expand ""
//! expand $
//! syntax errors
//! store everything
 
/*
 redirs sao argumentos
 ls > outfile ./path_to_ls   => vai outputar ls no path na outfile -.-"
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
    char    *space_input;
    char    **token_arr;
    
    if (!shell->input || !*shell->input)
        return ;
    space_input = ft_space_tokens(shell->input);
    token_arr = ft_split_tokens(space_input);
    free(space_input);
    
    //* .....    
    //* .....    
    //* .....    
}
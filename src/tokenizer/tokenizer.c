/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:50:16 by artuda-s          #+#    #+#             */
/*   Updated: 2024/10/11 10:22:54 by artuda-s         ###   ########.fr       */
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



void    ft_tokenizer(t_shell *shell)
{
    char    *space_input;
    char    **token_arr;

    if (!shell->input || !*shell->input)
        return ;
    space_input = ft_space_tokens(shell->input);
    token_arr = ft_split_tokens(space_input);
    free(space_input);
    if (ft_find_syntax_errors(token_arr))
    {
        ft_free_str_arr(token_arr);
        ft_error();
    }
    


   ft_free_str_arr(token_arr);
}

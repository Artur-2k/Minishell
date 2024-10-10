/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:50:16 by artuda-s          #+#    #+#             */
/*   Updated: 2024/10/10 22:15:51 by artuda-s         ###   ########.fr       */
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


static void	ft_free_token_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}


void    ft_tokenizer(t_shell *shell)
{
    char    *space_input;
    char    **token_arr;

    if (!shell->input || !*shell->input)
        return ;
    space_input = ft_space_tokens(shell->input);
    token_arr = ft_split_tokens(space_input);
    free(space_input);
    //ft_find_syntax_errors(token_arr);



   ft_free_token_arr(token_arr);
}

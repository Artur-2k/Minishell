/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:50:16 by artuda-s          #+#    #+#             */
/*   Updated: 2024/10/15 14:16:02 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO 🗹
//* free the array
//* read into an array of tokens 🗹
//* syntax errors
//* expand "" 
//* expand $

//! add a struct for shell to point to
//! store everything

// Goes through each token and extends each token
static int	ft_expand_tokens(char **tkn_arr, t_envp *envp)
{
	int     i;
	char    *temp;

	i = 0;
	while (tkn_arr[i])
	{
		temp = tkn_arr[i];
		tkn_arr[i] = ft_expand_token(tkn_arr[i], envp);
		free(temp);
		i++;
	}
	return (0);
}

int	ft_tokenizer(t_shell *shell)
{
    char    *space_input;
    char    **token_arr;

    if (!shell->input || !*shell->input)
        return (-1);

    space_input = ft_space_tokens(shell->input);
    token_arr = ft_split_tokens(space_input);
    free(space_input);

	if (ft_find_syntax_errors(token_arr))
		return(ft_free_str_arr(token_arr), -2);

	if (ft_expand_tokens(token_arr, shell->my_envp_h))
		return(ft_free_str_arr(token_arr), -3);

	for (int i =0; token_arr[i]; i++)
		printf("[%d] : [%s]\n", i, token_arr[i]);

   ft_free_str_arr(token_arr);
   return 0;
}

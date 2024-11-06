/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:50:16 by artuda-s          #+#    #+#             */
/*   Updated: 2024/11/04 12:48:04 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Goes through each token and extends each token
static int	ft_expand_tokens(char **tkn_arr, t_shell *shell)
{
	int     i;

	i = 0;
	while (tkn_arr[i])
	{
		errno = 0;
		shell->tokens[i]->token = ft_expand_token(tkn_arr[i], shell); //! falta a partir daqui
		if (errno == EMALLOC)
			return (ft_putstr_fd("Malloc error, sir\n", 2), 1);
		if (!shell->tokens[i]->token && i >= 1 &&
			shell->tokens[i - 1]->type != EXEC &&
			shell->tokens[i - 1]->type != PIPE)
		{
			return (ft_what_happened(tkn_arr[i], "ambiguous redirect"), 2); // error
		}
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

    // Uniforming data
	space_input = ft_space_tokens(shell->input); //*✅*//
    if (!space_input)
		return (-4);

	// Splitting data into tokens
	token_arr = ft_split_tokens(space_input); //*✅*//
    free(space_input);
	if (!token_arr)
		return (-5);

	// Checks for syntax errors
	if (ft_find_syntax_errors(token_arr)) //*✅*//
		return(ft_free_str_arr(token_arr), -2);

	// (for tokenization on expandables might want to transform into a linked list)
	// Creates a t_token** with an int type
	if (ft_emenda(token_arr, shell)) //*✅*//
		return(ft_free_str_arr(token_arr), -3);

	// Expands the tokens and sets it to the token array 
	if (ft_expand_tokens(token_arr, shell)) //*✅*//
		return(ft_free_str_arr(token_arr),
				ft_free_tokens(shell->tokens), -4);
   	ft_free_str_arr(token_arr);

	// Builds a right descendent recursive tree-like data structure (it's easy relax)
	shell->cmd_tree = ft_build(shell->tokens, shell); //*✅*//
	if (!shell->cmd_tree)
		return (-6);

	ft_free_tokens(shell->tokens);
   	return 0; // Success
}

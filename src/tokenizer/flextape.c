/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flextape.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 18:00:54 by artuda-s          #+#    #+#             */
/*   Updated: 2024/10/30 18:22:22 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * @brief Matches the token to a type
 * @param tkn The token string
 * @return Returns the type of token
*/
static int ft_find_type(char *tkn)
{
	if (!ft_strcmp(tkn, "|"))
		return (PIPE);
	else if (!ft_strcmp(tkn, "<"))
		return (INREDIR);
	else if (!ft_strcmp(tkn, "<<"))
		return (HDREDIR);
	else if (!ft_strcmp(tkn, ">"))
		return (OUTREDIR);
	else if (!ft_strcmp(tkn, ">>"))
		return (APPREDIR);
	else
		return (EXEC);
}


int	ft_emenda(char **tkn_arr, t_shell *shell)
{
	int	i;

	// Token lenght
	i = 0;
	while (tkn_arr[i])
		i++;

	shell->tokens = (t_tokens **)ft_calloc(i + 1, sizeof(t_tokens*));
	if (!shell->tokens)
		return (1); // malloc error

	// Allocate and set tokens from `tkn_arr`
	i = 0;
	while (tkn_arr[i])
	{
		shell->tokens[i] = (t_tokens *)ft_calloc(1, sizeof(t_tokens));
		if (!shell->tokens[i])
		{
			ft_free_tokens(shell->tokens);
			ft_putstr_fd("Malloc error, sir\n", 2);
			return (2);
		}

		// Matches the type of token
		shell->tokens[i]->type = ft_find_type(tkn_arr[i]);
		// Saves the actual token
		shell->tokens[i]->token = ft_strdup(tkn_arr[i]);
		i++;
	}
	return (0);
}

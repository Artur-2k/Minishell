/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:50:16 by artuda-s          #+#    #+#             */
/*   Updated: 2024/10/28 18:41:24 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (!tkn_arr[i] && i >= 1 && ft_strchr("<>", tkn_arr[i - 1][0]))
		{
			ft_what_happened(temp, "ambiguous redirect");
			return (free(temp), 1); // error
		}
		free(temp);
		i++;
	}
	return (0);
}

int	ft_emenda(char **tkn_arr, t_shell *shell)
{
	int	i;

	i = 0;
	while (tkn_arr[i])
		i++;
	shell->tkn_types = (int *)malloc(sizeof(int) * i);
	if (!shell->tkn_types)
		return (1); //error
	i = 0;
	while (tkn_arr[i])
	{
		if (!ft_strcmp(tkn_arr[i], "|"))
			shell->tkn_types[i] = PIPE;
		else if (!ft_strcmp(tkn_arr[i], "<"))
			shell->tkn_types[i] = INREDIR;
		else if (!ft_strcmp(tkn_arr[i], "<<"))
			shell->tkn_types[i] = HDREDIR;
		else if (!ft_strcmp(tkn_arr[i], ">"))
			shell->tkn_types[i] = OUTREDIR;
		else if (!ft_strcmp(tkn_arr[i], ">>"))
			shell->tkn_types[i] = APPREDIR;
		else
			shell->tkn_types[i] = EXEC;
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
	token_arr = ft_split_tokens(space_input);
    free(space_input);
	if (!token_arr)
		return (-5);

	if (ft_find_syntax_errors(token_arr))
		return(ft_free_str_arr(token_arr), -2);
	
	if (ft_emenda(token_arr, shell))
		return(ft_free_str_arr(token_arr), -3);

	if (ft_expand_tokens(token_arr, shell->my_envp_h)) // todo error checking
		return(free(shell->tkn_types), ft_free_str_arr(token_arr), -4);


	shell->n = 0;
	shell->cmd_tree = ft_build(token_arr, shell);

	free(shell->tkn_types);
   	ft_free_str_arr(token_arr);
   	return 0;
}

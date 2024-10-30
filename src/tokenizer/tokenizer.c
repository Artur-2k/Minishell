/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:50:16 by artuda-s          #+#    #+#             */
/*   Updated: 2024/10/30 18:12:33 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



// Goes through each token and extends each token
static int	ft_expand_tokens(char **tkn_arr, t_shell *shell)
{
	int     i;
	char	*temp;
	i = 0;
	while (tkn_arr[i])
	{
		temp = shell->tokens[i]->token;
		shell->tokens[i]->token = ft_expand_token(tkn_arr[i], shell->my_envp_h);
		if (!shell->tokens[i]->token && i >= 1 &&
			shell->tokens[i - 1]->type != EXEC &&
			shell->tokens[i - 1]->type != PIPE)
		{
			ft_what_happened(tkn_arr[i], "ambiguous redirect");
			return (free(temp), 1); // error
		}
		i++;
 		free(temp);
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

	if (ft_find_syntax_errors(token_arr))
		return(ft_free_str_arr(token_arr), -2);

	for (int i = 0; token_arr[i]; i++)
		printf("[%s]\n", token_arr[i]);

	// creates a t_token** with the char* token and int type
	if (ft_emenda(token_arr, shell))
		return(ft_free_str_arr(token_arr), -3);

	printf("------------\n");
	for (int i = 0; shell->tokens[i]; i++)
		printf("[%d] : [%s]\n", shell->tokens[i]->type, shell->tokens[i]->token);
	printf("------------\n");


	if (ft_expand_tokens(token_arr, shell)) // todo error checking
		return(ft_free_str_arr(token_arr), -4);

	printf("-----EXPANDED-----\n");
	for (int i = 0; shell->tokens[i]; i++)
		printf("[%d] : [%s]\n", shell->tokens[i]->type, shell->tokens[i]->token);
	printf("------------------\n");


	shell->cmd_tree = ft_build(shell->tokens, shell);

	printf("----Tree-----\n");
	print_tree(shell->cmd_tree);
	printf("------------\n");


	ft_free_tokens(shell->tokens);
   	ft_free_str_arr(token_arr);
   	return 0;
}

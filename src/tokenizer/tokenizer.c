/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:50:16 by artuda-s          #+#    #+#             */
/*   Updated: 2024/10/29 19:44:08 by artuda-s         ###   ########.fr       */
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
		shell->tokens[i]->token = ft_expand_token(tkn_arr[i], shell->my_envp_h);
		if (!shell->tokens[i]->token && i >= 1 && ft_strchr("<>", shell->tokens[i - 1]->token[0]))
		{
			ft_what_happened(tkn_arr[i], "ambiguous redirect");
			return (1); // error
		}
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
	shell->tokens = (t_tokens **)malloc(sizeof(t_tokens*) * i + 1);
	if (!shell->tokens)
		return (1); // malloc error
	i = 0;
	while (tkn_arr[i])
	{
		shell->tokens[i] = (t_tokens *)malloc(sizeof(t_tokens));
		if (!shell->tokens[i]){};// TODO malloc error
		if (!shell->tokens[i]){}; //TODO malloc error
		
		if (!ft_strcmp(tkn_arr[i], "|"))
			shell->tokens[i]->type = PIPE;
		else if (!ft_strcmp(tkn_arr[i], "<"))
			shell->tokens[i]->type = INREDIR;
		else if (!ft_strcmp(tkn_arr[i], "<<"))
			shell->tokens[i]->type = HDREDIR;
		else if (!ft_strcmp(tkn_arr[i], ">"))
			shell->tokens[i]->type = OUTREDIR;
		else if (!ft_strcmp(tkn_arr[i], ">>"))
			shell->tokens[i]->type = APPREDIR;
		else
			shell->tokens[i]->type = EXEC;
		shell->tokens[i]->token = ft_strdup(tkn_arr[i]);
		i++;
	}
	shell->tokens[i] = NULL;
	return (0);
}


/*
 * $a		echo		ola		$a 
 * NULL		echo		ola		NULL
 * EXEC		EXEC		EXEC	EXEC
*/



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

	printf("------------\n");
	print_tree(shell->cmd_tree);
	printf("------------\n");

   	ft_free_str_arr(token_arr);
   	return 0;
}

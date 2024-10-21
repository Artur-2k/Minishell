/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:50:16 by artuda-s          #+#    #+#             */
/*   Updated: 2024/10/21 17:57:15 by artuda-s         ###   ########.fr       */
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
		free(temp);
		i++;
	}
	return (0);
}



/* 
 *	
  ! print tree
 *
*/

void	print_tree(t_cmd *cmd)
{
	if (cmd->type == EXEC)
	{
		t_exec	*exec = (t_exec *)cmd;
		//* AV
		for (int i = 0; exec->av[i]; i++)
			printf("AV[%i]: [%s]\n", i , exec->av[i]);
		// redir list	
		t_redir *curr = exec->redir_list;
		while (curr != NULL)
		{
			// type de redir
				printf("TIPO DE REDIR: %i\n", curr->type);
			// redir
				printf("redir: [%s]\n", curr->redir);
			curr = curr->next;
		}		
	}
	else if (cmd->type == PIPE)
	{
		t_pipe *pipe = (t_pipe *)cmd;
		// chamar para printar esquerdo
		print_tree((t_cmd *)pipe->left);
		// chamar para a direita
		print_tree((t_cmd *)pipe->right);
	}
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

	if (ft_expand_tokens(token_arr, shell->my_envp_h)) // todo error checking
		return(ft_free_str_arr(token_arr), -3);

	for (int i = 0; token_arr[i]; i++)
		printf("%i: %s\n", i, token_arr[i]);
	shell->cmd_tree = ft_build(token_arr);
    
   	ft_free_str_arr(token_arr);
   	return 0;
}

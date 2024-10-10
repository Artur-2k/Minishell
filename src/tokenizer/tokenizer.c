/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:50:16 by artuda-s          #+#    #+#             */
/*   Updated: 2024/10/10 17:06:33 by artuda-s         ###   ########.fr       */
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
/* void ft_error()
{
    
} */


bool    ft_check_unclosed_quotes(char **tkn_arr)
{
    int     i;
    int     j;
    char    quote_char;
    
    j = 0;
    while (tkn_arr[++j])
    {
        i = 0;
        while (tkn_arr[j][i])
        {
            if (tkn_arr[j][i] == '\'' || tkn_arr[j][i] == '"')
            {
                quote_char = tkn_arr[j][i++];
                while (tkn_arr[j][i] && tkn_arr[j][i] != quote_char)
                    i++;
                if (tkn_arr[j][i] != quote_char)
                    return (true);
                i++;
            }
            else
                i++;
        }
        j++;
    }
    return (false);
}
/* 

bool    ft_check_double_redireciton(char *token)
{
    
}
static void ft_find_syntax_errors(char **tkn_arr)
{
 *   double pipe token          ...     | |        ...          X
 *   pipe at the start and end   | .................|           X
 *   pipe or redir              ...     | >                     x
 *   double redir token         ...  << >  > <  >> < ...          X
 *   heredoc no eof             ...  <<{nothing after}          X
 *   > >> e < without file      ...   > file < file >> file ... X
 *   "" '' nao fechadas
 *      /MAIS NAO PLEASE T-T
    
    if (ft_check_unclosed_quotes(tkn_arr)) //todo
        ft_error(); // todo
    if (ft_check_double_redireciton(tkn_arr)) // todo atencao aspas
        ft_error();
    if (ft_check_pipes(tkn_arr)) // todo  atencao aspas
        ft_error();
    if (ft_check_redirs(tkn_arr)) // todo atencao aspas
        ft_error();
    
} */

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

    for (int i = 0; token_arr[i]; i++)
        printf("token : [%s]\thas unclosed quotes: [%d]\n", token_arr[i], ft_check_unclosed_quotes(token_arr));
    
    

   ft_free_token_arr(token_arr);
}

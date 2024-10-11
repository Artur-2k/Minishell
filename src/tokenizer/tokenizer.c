/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:50:16 by artuda-s          #+#    #+#             */
/*   Updated: 2024/10/11 22:37:51 by artuda-s         ###   ########.fr       */
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

char	*ft_expand_token(char* token)
{
	/*
	 * $KEY  	=> expand
	 * "$KEY"	=> expand + remove ""
	 * ''		=> remove ''
	*/
	int		i;
	int		j;
	char	quote_char;
	char	*new;

	j = 0;
	i = 0;
	while(token[i])
	{
		if (token[i] == '\'' || token[i] == '"')
		{
            quote_char = token[i++];
			while (token[i] && token[i] != quote_char) //todo aspas
			{
                i++;
			}
		}
		else if (token[i] == '$' && token[i + 1])
		{
			if (token[i] == token[i + 1]) // $$
				new = ft_expand_to_pid();//todo
			else if(token[++i] == "\"" || token[i] == "\'") //todo $"str" => PATH & $'str' => str
				new = ft_handle_this_shit(); //todo
			else if(token[++i]) // $key
			{
				int len  = 0;
				// $PATH"
				/* len = 0
				 * P ✅ len 1
				 * A ✅ len 2
				 * T ✅ len 3
				 * H ✅ len 4
				 * \0 X
				*/
				while (token[i] && !ft_strchr("\"\'$", token[i]))
				{
					i++;
					len++;
				}
				new = ft_expand_to_value(&token[i], len); // todo (len da para ver quanto do token leio ate substituir no caso de encontrar " ' se len= 0 e ate ao fim)
			}
		}



		i++;
	}

	return (0); // success
}

int	ft_expand_tokens(char **tkn_arr, t_envp *envp)
{
	/*
	 * "$KEY" expands to value and if key not found expands to ""
	 * '$KEY' doesnt
	*/

	int	i;
	int	j;

	i = 0;
	while (tkn_arr[i])
	{
		j = 0;
		{

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

    space_input = ft_space_tokens(shell->input);
    token_arr = ft_split_tokens(space_input);
    free(space_input);

    if (ft_find_syntax_errors(token_arr))
        return(ft_free_str_arr(token_arr), -2);

	if (ft_expand_tokens(token_arr, shell))
        return(ft_free_str_arr(token_arr), -3);




   ft_free_str_arr(token_arr);
   return 0;
}

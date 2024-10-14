/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:50:16 by artuda-s          #+#    #+#             */
/*   Updated: 2024/10/14 19:00:41 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO 🗹
//* free the array
//* read into an array of tokens 🗹
//* syntax errors

//! expand ""
//! expand $
//! add a struct for shell to point to
//! store everything



char	*ft_expand_token(char* token, t_envp *envp)
{
	char	*new;

	new = NULL;
	while (*token)
	{
		if (*token == '\'') // single quotes
		{
			token++;
			while (*token && *token != '\'')
			{
				new = ft_append_char_to_str(new, *token);
				token++;
			}
		}
		else if (*token == '\"') // double quotes
		{
			token++;
			while (*token && *token != '\"')
			{
				if (*token != '$') // normal letter
					new = ft_append_char_to_str(new, *token);
				else
				{
					token++;
					if (!*token) // nunca vai acontecer se correr tudo bem xd
						break ;
					else if (*token == '\"') // "...$"
					{
						ft_append_char_to_str(new, '$');
						break ;
					}
					else if (*token == '$') // "...$$asd"
						new = ft_strjoin(new, ft_itoa(ft_get_pid()));
					else // "$key"
					{
						int len = 1;
						while (token[len] != '\"' && token[len] != '\'' && token[len] != ' ')
							len++;
						if (ft_has_key(token, envp))
						{
							char *key = ft_substr(token, 0, len);
							new = ft_strjoin(new, ft_get_value(key, envp));
							free(key);
							token += len - 1; // -1 para nao saltar dois a seguir
						}
					}
				}
				token++;
			}
		}
		else if (*token == '$') // normal expandables
		{
			token++;
			if (!*token) // ... $ => ... $
			{
				new = ft_append_char_to_str(new, '$');
				break ;
			}
			else if (*token == '\"' || *token == '\'') // ...$"..." => ......
				continue ;
			else if (*token == '$') // ...$$asd  
				new = ft_strjoin(new, ft_itoa(ft_get_pid()));
			else // "$key"
			{
				int len = 0;
				while (token[len] && token[len] != '\"' && token[len] != '\'' && token[len] != ' ')
					len++;
				if (ft_has_key(token, envp))
				{
					char *key = ft_substr(token, 0, len);
					new = ft_strjoin(new, ft_get_value(key, envp));
					free(key);
					token += len- 1; // ola"
				}
			}
		}
		else // normal char
			new = ft_append_char_to_str(new, *token);

		token++;
	}
	return (new); // success
}

int	ft_expand_tokens(char **tkn_arr, t_envp *envp)
{
	/*
	 * "$KEY" expands to value and if key not found expands to ""
	 * '$KEY' doesnt
	*/

	int	i;
	char *temp;

	i = 0;
	while (tkn_arr[i])
	{
		temp = tkn_arr[i];
		tkn_arr[i] = ft_expand_token(tkn_arr[i], envp);
		free(temp);
		i++;
	}
	printf("ola mundo\n");
	for (int j = 0; tkn_arr[j] != NULL; j++)
		printf("%d: %s\n", j, tkn_arr[j]);

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




   ft_free_str_arr(token_arr);
   return 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:50:23 by artuda-s          #+#    #+#             */
/*   Updated: 2024/11/21 13:42:48 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * @brief Will search for a white space that is not quoted and count the number
 * of tokens. Note: The string is already trimmed and has only 1 space between
 * tokens
 * @param str The string which will count tokens
 * @return The number of tokens
*/
static int	ft_count_tokens(char *str)
{
	char	quote_char;
	int		count;
	int		i;

	count = 0;
	i = 0;
	if (str[i])
		count = 1;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote_char = str[i++];
			while (str[i] && str[i] != quote_char)
				i++;
		}
		if (str[i] && str[i] == ' ' && str[i + 1])
			count++;
		if (str[i])
			i++;
	}
	return (count);
}

/*
 * @brief Will recieve a string and will count the lenght of the first token
 * (so if we need the second we should pass to this function the address of the
 * starting character of the token and so on). It ignores spaces that are between
 * quotes
 * @param str The string starting at the token we want to examine
 * @return The length of the current token
*/
static int	ft_token_lenght(char *str)
{
	int		len;
	char	quote_char;

	len = 0;
	while (str[len] && str[len] != ' ')
	{
		if (str[len] == '\'' || str[len] == '"')
		{
			quote_char = str[len++];
			while (str[len] && str[len] != quote_char)
				len++;
		}
		if (str[len])
			len++;
	}
	return (len);
}

/*
 * @brief Will find the token len and create a new allocated string
 * of the current token. Updates the starting to the end of the token
 * @param str The string to extract from
 * @param start The index of the starting char
 * @return The allocated extracted token. In case of error returns NULL
*/
static char	*ft_populate_tkn_arr(char *str, int *start)
{
	int		tkn_len;
	char	*ret;

	if (str[*start] == ' ')
		(*start)++;
	tkn_len = ft_token_lenght(&str[*start]);
	ret = ft_substr(str, *start, tkn_len);
	if (!ret)
		return (NULL);
	*start = *start + tkn_len;
	return (ret);
}

/*
 * @brief Starts by counting the number of tokens a proceeds to
 * duplicate each token into each element of the string array.
 * At the end NULL terminates the pointer array.
 * @param str The string to split into tokens
 * @return Returns a NULL terminated string array
 * with a token for each string. Return NULL if any error occurs
*/
char	**ft_split_tokens(char *str)
{
	char	**token_arr;
	int		no_tokens;
	int		i;
	int		start;

	if (!str || !*str)
		return (NULL);
	no_tokens = ft_count_tokens(str);
	token_arr = (char **)malloc(sizeof(char *) * (no_tokens + 1));
	if (!token_arr)
		return (ft_putstr_fd("Malloc error, sir\n", 2), NULL);
	i = 0;
	start = 0;
	while (i < no_tokens)
	{
		token_arr[i] = ft_populate_tkn_arr(str, &start);
		if (!token_arr[i])
			return (ft_free_str_arr(token_arr), NULL);
		i++;
	}
	token_arr[i] = NULL;
	return (token_arr);
}

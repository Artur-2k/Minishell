/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:50:23 by artuda-s          #+#    #+#             */
/*   Updated: 2024/10/27 22:54:04 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int  ft_count_tokens(char *str)
{
	char	quote_char;
    int     count;
    int     i;

    count = 0;
    i = 0;
    if (str[i])
        count = 1;
    while(str[i])
    {
        if (str[i] == '\'' || str[i] == '"')
        {
            quote_char = str[i++];
            while (str[i] && str[i] != quote_char)
                i++;
        }
        if (str[i] && str[i] == ' ' && str[i + 1])
			count++;
        i++;
    }
    return (count);
}

static int	ft_token_lenght(char *str)
{
	int len;

	len = 0;
	while (str[len] && str[len] != ' ')
	{
        if (str[len] == '\'' || str[len] == '"')
        {
            char quote_char = str[len++];
            while (str[len] && str[len] != quote_char)
                len++;
        }
		len++;
	}
	return (len);
}

static char *ft_populate_tkn_arr(char *str, int *start)
{
    int         tkn_len;
    char        *ret;

    if (str[*start] == ' ')
        (*start)++;
    tkn_len = ft_token_lenght(&str[*start]);
    ret = ft_substr(str, *start, tkn_len);
    if (!ret)
        return (NULL);
    *start = *start + tkn_len;
    return (ret);
}

char    **ft_split_tokens(char *str)
{
    char    **token_arr;
    int     no_tokens;
    int     i;
    int     start;

    if (!str || !*str)
        return (NULL);
    no_tokens = ft_count_tokens(str); // no of tokens to be allocated
    token_arr = (char **)malloc(sizeof(char *) * (no_tokens + 1)); // null terminate the arrate too!
    i = 0;
    start = 0;
    while (i < no_tokens)
    {
        token_arr[i] = ft_populate_tkn_arr(str, &start); // fetches the token
        if (!token_arr[i])
            return (ft_free_str_arr(token_arr), NULL);
        i++;
    }
    token_arr[i] = NULL; // null terminates
    return (token_arr);
}

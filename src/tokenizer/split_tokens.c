/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:50:23 by artuda-s          #+#    #+#             */
/*   Updated: 2024/10/09 17:50:24 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int  ft_count_tokens(char *str)
{
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
            char quote_char = str[i++];
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
char    **ft_split_tokens(char *str)
{
    char    **token_arr;

    //alocar memoria
    // quantos tokens?  [ola teste "ol   a" teste] ==> 3
    int no_tokens = ft_count_tokens(str);
    printf("no_tokens = %d\n", no_tokens);

    token_arr = (char **)malloc(sizeof(char *) * no_tokens + 1);

    int i = 0;
    int start = 0;
    int tknlen = 0;
    while (i < no_tokens)
    {
        if (str[start] == ' ')
            start++;
        tknlen = ft_token_lenght(&str[start]);
        token_arr[i] = ft_substr(str, start, tknlen);
        start += tknlen;
        i++;
    }
    token_arr[i] = NULL;

    for (int z = 0; token_arr[z] != NULL; z++)
        printf("i: %d  ->  [%s]\n", i, token_arr[z]);

    return (token_arr);
}

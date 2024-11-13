/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:15:42 by artuda-s          #+#    #+#             */
/*   Updated: 2024/11/13 14:26:10 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Will look for a quote char and then skip all chars until the same
 * quote char is found. If none is found and the string ends returns (open quote flag)
 */
static bool    ft_check_unclosed_quotes(char **tkn_arr)
{
    int     i;
    int     j;
    char    quote_char;

    j = 0;
    while (tkn_arr[j])
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

/**
 *	@brief	Checks for pipe at the beggining, the double redir token or redir token
 * at the end (> >> < << |)
 * *
 * 	NOTE: each redir is a token
 */
static bool    ft_check_redirecitons(char **tkn_arr)
{
	int	i;

	i = 0;
	// pipe no inicio
	if (tkn_arr[0] && tkn_arr[0][0] == '|')
		return (ft_printf("Parse error near %c\n", tkn_arr[i][0]), true);

	// double redirs ||  >< >| |>(valido)...
	while (tkn_arr[i] != NULL)
	{
        if (tkn_arr[i][0] == '|' &&  tkn_arr[i + 1] && tkn_arr[i + 1][0] == '|')
		        return (ft_printf("Parse error near %c\n", tkn_arr[i][0]), true);
        else if (ft_strchr("<>", tkn_arr[i][0]))
		{
            if (tkn_arr[i + 1] && ft_strchr("<|>", tkn_arr[i + 1][0]))
		        return (ft_printf("Parse error near %c\n", tkn_arr[i][0]), true);
		}
		i++;
	}

	// > < | at the end(double redir are filtered)
	--i;
    if (ft_strchr("<>", tkn_arr[i][0]))
        return (ft_printf("Parse error near %c\n", tkn_arr[i][0]), true);
    else if (tkn_arr[i][0] == '|')
		return (ft_printf("Minihell doens't handle | at the end\n", true));
	return (false);
}

/**
 * @brief	Will basically check for open quotes, redirecs at the end, pipe at the start
 * and redirects mixed with pipes and stuff like that (>< >>> >|| ...)
 */
int ft_find_syntax_errors(char **tkn_arr) // todo VER qual caso nao da erro <> ou >< e corrigir
{
/*
 *   pipe at the start and end   | .................|           ✅
 *   heredoc no eof             ...  <<{nothing after}          ✅
 *   > >> e < without file      ...   > file < file >> file ... ✅
 *   double pipe token          ...     | |        ...          ✅
 *   pipe or redir              ...     | > valid               ✅
 *   double redir token         ...  << >  > <  >> < ...        ✅
 *   "" '' nao fechadas											✅
 *      /MAIS NAO PLEASE T-T ❌
*/
    if (ft_check_unclosed_quotes(tkn_arr))
        return (ft_printf("Minihell doenst handle unclosed quotes\n"), 1);
    if (ft_check_redirecitons(tkn_arr))
        return (1);

    return (0);
}
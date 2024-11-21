/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:50:25 by artuda-s          #+#    #+#             */
/*   Updated: 2024/11/21 13:39:42 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#define ERROR 2

/*
 *  Adds the first quote and while it doesnt find the end or the second quote
 *  it keeps appending a char to the newstring and if there is a seconde quote
 *  appends the quote
*/
static char	*ft_is_quoted(char *str, char *nstr, int *flag, int *i)
{
	char	quote_char;

	quote_char = str[*i];
	nstr = ft_append_char_to_str(nstr, str[(*i)++]);
	while (nstr && str[*i] && str[*i] != quote_char)
		nstr = ft_append_char_to_str(nstr, str[(*i)++]);
	if (nstr && str[*i])
		nstr = ft_append_char_to_str(nstr, str[(*i)++]);
	if (!nstr)
		return (*flag = ERROR, nstr);
	*flag = true;
	return (nstr);
}

/*
 * If the add space flag is true adds a space before the redir
 * Adds either one or two redirs (<< and >>) and skips 
 * If there is something after the redir adds a space and turns the space 
 * flag off
*/
static char	*ft_append_redir(char *str, char *nstr, int *flag, int *i)
{
	if (*flag == true)
	{
		nstr = ft_append_char_to_str(nstr, ' ');
		if (!nstr)
			return (*flag = ERROR, NULL);
	}
	if (str[*i] == str[*i + 1])
	{
		nstr = ft_append_char_to_str(nstr, str[(*i)++]);
		if (!nstr)
			return (*flag = ERROR, NULL);
		nstr = ft_append_char_to_str(nstr, str[(*i)++]);
	}
	else
		nstr = ft_append_char_to_str(nstr, str[(*i)++]);
	if (nstr && str[*i])
		nstr = ft_append_char_to_str(nstr, ' ');
	if (!nstr)
		return (*flag = ERROR, NULL);
	*flag = false;
	return (nstr);
}

/*
 * If the add space flag is true adds a space before the pipe
 * If there is something after the pipe adds a space and turns the space flag off
*/
static char	*ft_append_pipe(char *str, char *nstr, int *flag, int *i)
{
	if (*flag == true)
	{
		nstr = ft_append_char_to_str(nstr, ' ');
		if (!nstr)
			return (*flag = ERROR, NULL);
	}
	nstr = ft_append_char_to_str(nstr, str[(*i)++]);
	if (nstr && str[*i])
		nstr = ft_append_char_to_str(nstr, ' ');
	if (!nstr)
		return (*flag = ERROR, NULL);
	*flag = false;
	return (nstr);
}

/* 
 * If the space flag is true adds a space
 * While the string is a space skips and then turns the space flag off
*/
static char	*ft_spacing(char *str, char *nstr, int *flag, int *i)
{
	if (*flag == true)
	{
		nstr = ft_append_char_to_str(nstr, ' ');
		if (!nstr)
			return (*flag = ERROR, NULL);
	}
	while (str[*i] && ft_isspace(str[*i]))
		(*i)++;
	*flag = false;
	return (nstr);
}

/*
 * Removes spaces before and after the tokens
 * Removes extra spaces from non quoted multi spaced tokens
 * Adds a space when there is none after and before special tokens (<>|)
 * Each token is either a string (quotes are handled), a redir and a pipe
*/
char	*ft_space_tokens(char *str)
{
	int		flag;
	char	*nstr;
	int		i;

	i = 0;
	flag = false;
	nstr = NULL;
	str = ft_trim(str);
	while (str && str[i] && flag != ERROR)
	{
		if (str[i] == '\'' || str[i] == '"')
			nstr = ft_is_quoted(str, nstr, &flag, &i);
		else if (str[i] == '<' || str[i] == '>')
			nstr = ft_append_redir(str, nstr, &flag, &i);
		else if (str[i] == '|')
			nstr = ft_append_pipe(str, nstr, &flag, &i);
		else if (ft_isspace(str[i]))
			nstr = ft_spacing(str, nstr, &flag, &i);
		else
		{
			nstr = ft_append_char_to_str(nstr, str[i++]);
			flag = true;
		}
	}
	return (nstr);
}

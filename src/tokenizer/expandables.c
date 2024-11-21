/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandables.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:14:05 by artuda-s          #+#    #+#             */
/*   Updated: 2024/11/21 13:32:25 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Just removes the single quotes and copies what is inside
static char	*ft_expand_squotes(char *new, char	**token)
{
	(*token)++;
	while (**token && **token != '\'')
	{
		new = ft_append_char_to_str(new, **token);
		if (!new)
			return (errno = EMALLOC, NULL);
		(*token)++;
	}
	return (new);
}

// Copies the value of the environment variable if there is one and
// concatenates to the new token and if there wasnt one doesnt add nothing
// and just skips the $key
static char	*ft_expand_variable(char *new, char **token, t_envp *envp)
{
	int		len;
	char	*key;

	key = NULL;
	len = 0;
	while ((*token)[len] &&
			(*token)[len] != '\"' &&
			(*token)[len] != '\'' &&
			(*token)[len] != ' ' &&
			(*token)[len] != '$')
		len++;
	if (ft_has_key(*token, len, envp))
	{
		key = ft_substr(*token, 0, len);
		if (!key)
			return (errno = EMALLOC, NULL);
		new = ft_strappend(new, ft_get_value(key, envp));
		free(key);
		if (!new)
			return (errno = EMALLOC, NULL);
	}
	(*token) += len - 1;
	return (new);
}

// while there is no expansion it just copies the same way as squote
// in the case or $"" it just appends the $
// no need to check for $\0 cuz there we've made sure it has ending quotes
// extra: $$ isnt asked but i handled
static char	*ft_expand_dquotes(char *new, char **token, t_shell *shell)
{
	(*token)++;
	while (**token && **token != '\"')
	{
		if (**token != '$')
			new = ft_append_char_to_str(new, **token);
		else
		{
			(*token)++;
			if (**token == ' ')
				new = ft_strappend(new, "$ ");
			else if (**token == '\"' || **token == ' ')
				new = ft_append_char_to_str(new, '$');
			else if (**token == '$')
				new = ft_strappend(new, shell->spid);
			else if (**token == '?')
				new = ft_strappend(new, shell->sexit_status);
			else
				new = ft_expand_variable(new, token, shell->my_envp_h);
		}
		if (errno == EMALLOC)
			return (NULL);
		(*token)++;
	}
	return (new);
}

//
static char	*ft_expand_noquotes(char *new, char **token, t_shell *shell)
{
	(*token)++;
	if (!**token || **token == ' ')
		new = ft_append_char_to_str(new, '$');
	else if (**token == '$')
		new = ft_strappend(new, shell->spid);
	else if (**token == '?')
		new = ft_strappend(new, shell->sexit_status);
	else
		new = ft_expand_variable(new, token, shell->my_envp_h);
	if (errno == EMALLOC)
		return (NULL);
	return (new);
}

// Checks each character and see what it has to do
// See next functions
char	*ft_expand_token(char *token, t_shell *shell)
{
	char	*new;

	new = NULL;
	if (!ft_strcmp("\"\"", token) || !ft_strcmp("\'\'", token))
		return (ft_strdup(""));
	while (*token)
	{
		if (*token == '\'')
			new = ft_expand_squotes(new, &token);
		else if (*token == '\"')
			new = ft_expand_dquotes(new, &token, shell);
		else if (*token == '$')
			new = ft_expand_noquotes(new, &token, shell);
		else
			new = ft_append_char_to_str(new, *token);
		if (errno == EMALLOC)
			return (NULL);
		if (*token)
			token++;
	}
	return (new);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandables.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:14:05 by artuda-s          #+#    #+#             */
/*   Updated: 2024/10/30 17:56:12 by artuda-s         ###   ########.fr       */
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
		(*token)++;
	}
	return (new);
}

// Copies the value of the environment variable if there is one and
// concatenates to the new token and if there wasnt one doesnt add nothing
// and just skips the $key
static char	*ft_expand_variable(char *new, char **token, t_envp *envp)
{
	int	len;
	char *key;

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
		new = ft_strappend(new, ft_get_value(key, envp));
		free(key);
	}
	(*token) += len - 1; // -1 para nao saltar dois a seguir
	return (new);
}

// while there is no expansion it just copies the same way as squote
// in the case or $"" it just appends the $
// no need to check for $\0 cuz there we've made sure it has ending quotes
// extra: $$ isnt asked but i handled
static char	*ft_expand_dquotes(char *new, char **token, t_envp *envp)
{
	(*token)++;
	while (**token && **token != '\"')
	{
		if (**token != '$') // normal letter
			new = ft_append_char_to_str(new, **token);
		else
		{
			(*token)++;
			if (**token == '\"') // "...$"
				ft_append_char_to_str(new, '$');
			else if (**token == '$') // "...$$asd"
				new = ft_strappend(new, ft_itoa(ft_get_pid()));
			else // "$key"
				new = ft_expand_variable(new, token, envp);
		}
		(*token)++;
	}
	return (new);
}

//
static char	*ft_expand_noquotes(char *new, char **token, t_envp *envp)
{
	(*token)++;
	if (!**token || (**token == '\"' || **token == '\'')) // ... $ => ... $ || ...$"..."  ==> ...$...
		new = ft_append_char_to_str(new, '$');
	else if (**token == '$') // ...$$asd
		new = ft_strappend(new, ft_itoa(ft_get_pid()));
	else // "$key"
		new = ft_expand_variable(new, token, envp);
	return (new);
}

// Checks each character and see what it has to do
// See next functions
char	*ft_expand_token(char *token, t_envp *envp)
{
	char	*new;

	new = NULL;
	if (!ft_strcmp("\"\"", token) || !ft_strcmp("\'\'", token))
		return (ft_strdup(""));
	while (*token)
	{
		if (*token == '\'') // single quotes
			new = ft_expand_squotes(new, &token);
		else if (*token == '\"') // double quotes
			new = ft_expand_dquotes(new, &token, envp);
		else if (*token == '$') // normal expandables
			new = ft_expand_noquotes(new, &token, envp);
		else // normal char
			new = ft_append_char_to_str(new, *token);
		if (*token) // So we dont go after the string ends
			token++;
	}
	return (new); // success
}

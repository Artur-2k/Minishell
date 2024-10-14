#include "minishell.h"

bool	ft_has_key(char *try, int len,  t_envp *envp)
{
	if (!*try || !try || !envp)
		return (false);
	while (envp != NULL)
	{
		if (!ft_strncmp(try, envp->key, len))
			return (true);
		envp = envp->next;
	}
	return (false);
}

char *ft_get_value(char *key, t_envp *envp)
{
	if (!key || !*key || !envp)
		return ("");

	while (envp != NULL)
	{
		if (!ft_strcmp(key, envp->key))
			return (envp->value);
		envp =envp->next;
	}
	return ("");
}



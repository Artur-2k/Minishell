/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 09:30:01 by artuda-s          #+#    #+#             */
/*   Updated: 2024/11/12 22:38:16 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
?   export
        "declare - x " + key + "=" + "\"" + value + "\""
            declare - x USER="artuda-s"


?    export  z
?        env             export
        ----            declare -x z

?    export  zz=
?        env             export
        zz=            declare -x zz=""


?    export  zzzz=a
?        env             export
        zzzz=a           declare -x zzzz="a"

?    export  z   zz=   zzzz=a
?       env             export
        ----            declare -x z
        zz=             declare -x zz=""
        zzzz=a          declare -x zzzz="a"
*/



static bool	ft_valid_identifier(char *key)
{
	if (!key || !*key || ft_isdigit(*key))
		return (false);

	while (key && *key)
	{
		if (!ft_isalnum(*key))
			return (false);
		key++;
	}
	return (true);
}


static void	ft_export_print(t_exec *cmd)
{
    t_envp  *cur;

    cur = cmd->shell->envp2lol_h;
    while (cur != NULL)
    {
        printf("declare -x %s", cur->key);
        if (cur->value) // ="..."
            printf("=\"%s\"", cur->value);
		printf("\n");
        cur = cur->next;
    }
	return ;
}

static void	ft_export_check_equal(t_exec *cmd, int i, char *key)
{
        char	*value;

        if (ft_strchr(cmd->av[i], '=')) // export a=asd  a=
        {

            if (cmd->av[i][0] == '\0')
                value = ft_strdup("");
            else
                value = ft_extract_value(cmd->av[i]);
            if (!value) {}; // TODO malloc error

            ft_add_entry_env(&cmd->shell->my_envp_h, key, value); //TODO  check for error
            ft_add_entry_env2(&cmd->shell->envp2lol_h, key, value); //TODO check for error
	        free(value);
	    }
        else // export a
        {
            value = NULL;
            if (!value) {}; // TODO malloc free
            ft_add_entry_env2(&cmd->shell->envp2lol_h, key, value); //todo
	        free(value);
        }
}


// envp ordenado exenvp
void    ft_export(t_exec *cmd)
{
    int		i;
    char	*key;

    // export
    if (cmd->av[1] == NULL)
		ft_export_print(cmd);
	else
    // export z     z=      z=abcde
    {
        i = 1;
        while (cmd->av[i])
        {
            key = ft_extract_key(cmd->av[i]);
			if (!ft_valid_identifier(key))
			{
				cmd->shell->exit_status = 1;
				ft_what_happened(cmd->av[i], "not a valid identifier, sir");
				i++;
				continue ;
			}
			ft_export_check_equal(cmd, i, key);
            free(key);
			i++;
        }
    }
}

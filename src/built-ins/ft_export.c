/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 09:30:01 by artuda-s          #+#    #+#             */
/*   Updated: 2024/11/13 16:26:15 by artuda-s         ###   ########.fr       */
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

#define ENV1    1
#define ENV2    2
#define REPLACE 3
#define APPEND  4

static bool	ft_valid_identifier(char *key)
{
	if (!key || !*key || *key == '+' || ft_isdigit(*key))
		return (false);

	while (key && *key)
	{
        if (*key == '+' && !*(key + 1))
            break ;            
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
        int     mode;

        mode = REPLACE;
        if (ft_strchr(cmd->av[i], '=')) // export a=asd  a=
        {
            if (ft_strchr(key, '+')) // export a+=as
            {
                mode = APPEND;
                key[ft_strlen(key) - 1] = 0;
            }   
            value = ft_extract_value(cmd->av[i]);
            ft_add_entry_env(&cmd->shell->my_envp_h, key, value, mode); 
            ft_add_entry_env2(&cmd->shell->envp2lol_h, key, value, mode);
	        free(value);
	    }
        else // export a
        {
            value = NULL;
            if (!value) {}; // TODO malloc free
            ft_add_entry_env2(&cmd->shell->envp2lol_h, key, value, mode);
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

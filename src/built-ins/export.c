/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 09:30:01 by artuda-s          #+#    #+#             */
/*   Updated: 2024/11/07 15:18:15 by artuda-s         ###   ########.fr       */
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

// envp ordenado exenvp
void    ft_export(t_exec *cmd)
{
    // export
    if (cmd->av[1] != NULL)
    {
        t_envp  *cur;

        cur = cmd->shell->envp2lol_h;
        while (cur != NULL)
        {
            printf("declare -x %s", cur->key);
            if (cur->value) // ="..."
                printf("=\"%s\"", cur->value);
            cur = cur->next;            
        }
    }

    // export z     z=      z=abcde
    {
        int i;

        i = 1;
        while (cmd->av[i])
        {
            char *key;
            char *value;
            
            key = ft_extract_key(cmd->av[i]); // TODO
            if (!key) {} // TODO malloc error
            
            if (ft_strchr(cmd->av[i], '=')) // export a=asd  a=
            {
                value = ft_extract_value(); // TODO
                if (!value) {} // TODO
            }
            else // export a
            {
                value = ft_strdup("");    
            }
            ft_add_entry_env(cmd->shell->envp2lol_h, key, value); //todo
            ft_add_entry_env2(cmd->shell->envp2lol_h, key, value); //todo
        }
    }   


    
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 09:30:01 by artuda-s          #+#    #+#             */
/*   Updated: 2024/11/07 18:18:31 by artuda-s         ###   ########.fr       */
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


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

int ft_add_entry_env(t_envp **head, char *key, char *value)
{

    if (ft_has_key(key, ft_strlen(key), *head))
    {
        t_envp *cur = *head;
        while (ft_strcmp(key, cur->key) != 0)
            cur = cur->next;
        if (cur->value)
            free(cur->value);
        cur->value = ft_strdup(value);
        if (!cur->value) // TODO malloc error
            return (1);
        return (0); // Success
    }
    
    if (*head == NULL)
    {
        *head = ft_new_env_node(key, value);
        if (!*head) // TODO malloc error
            return (1);
    }
    else
    {
        // Ir até ao fim e adicionar no final
        t_envp *temp = *head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = ft_new_env_node(key, value);
        if (!temp->next) // TODO malloc error
            return (2);
    }
    return (0); // Success
}

int     ft_add_entry_env2(t_envp **head, char *key, char *value)
{
    if (ft_has_key(key, ft_strlen(key), *head))
    {
        t_envp  *cur = *head;
        while (ft_strcmp(key, cur->key) != 0)
            cur = cur->next;
        if (cur->value)
            free(cur->value);
        cur->value = ft_strdup(value);
        if (!cur->value) // TODO malloc error
            return (1);
        return (0); // Success
    }

    t_envp  *new = ft_new_env_node(key, value);
    if (!new) //TODO malloc error
        return (1);
    
    if (*head == NULL || ft_strcmp((*head)->key, key) > 0)
    {
        new->next = *head;
        *head = new;
        return (0); // Success
    }
    
    t_envp  *cur = *head;
    // procurar sitio certo
    while (cur->next != NULL && ft_strcmp(cur->next->key, new->key) < 0)
        cur = cur->next;        
    new->next = cur->next;
    cur->next = new;

    return (0); // Success
}


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
            
            key = ft_extract_key(cmd->av[i]);
            if (!key) {} // TODO malloc error
            
            if (ft_strchr(cmd->av[i], '=')) // export a=asd  a=
            {
                if (cmd->av[i][0] == '\0')
                    value = ft_strdup("");    
                else
                    value = ft_extract_value(cmd->av[i]);
                if (!value) {}; // TODO malloc error

                ft_add_entry_env(cmd->shell->envp2lol_h, key, value); //TODO  check for error
                ft_add_entry_env2(cmd->shell->envp2lol_h, key, value); //TODO check for error
            }
            else // export a
            {
                value = ft_strdup("");
                if (!value) {}; // TODO malloc free
                ft_add_entry_env2(cmd->shell->envp2lol_h, key, value); //todo
            }
            free(key);
            free(value);
        }
    }   
}

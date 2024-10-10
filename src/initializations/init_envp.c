/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:37:00 by artuda-s          #+#    #+#             */
/*   Updated: 2024/10/10 13:33:34 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//todo Could add some error checking for malloc on
//todo    str dup, substr and t_envp
//!     Vale a pena checar se envp esta vazio? vai que 
//!     um ninja apaga tudo antes de rodar o minishell xD

static char     *ft_extract_key(char *line)
{
    char    *key;
    int     end;    

    key = NULL;
    end = 0;
    while (line && line[end])
    {
        if (line[end] == '=')
        {
            key = ft_substr(line, 0, end);
            break ;
        }    
        else
            end++;
    }
    return (key);
}

static char     *ft_extract_value(char *line)
{
    char    *value;
    int     start;

    value = NULL;
    start = 0;
    while (line && line[start])
    {
        if (line[start] == '=')
        {
            start++;
            value = ft_strdup(&line[start]);
            break ;
        }
        start++;
    }
    return (value);
}

static t_envp   *ft_new_node(char *envp_line)
{
    t_envp  *new_node;

    new_node = (t_envp*)malloc(sizeof(t_envp));

    new_node->key = ft_extract_key(envp_line);
    new_node->value = ft_extract_value(envp_line);
    new_node->next = NULL;
    return (new_node);
}

void    ft_init_envp(t_shell *shell, char *envp[])
{
    int i;
    t_envp  *curr;
    t_envp  *new;

    curr = NULL;
    i = 0; 
    shell->my_envp_h = NULL;
    while (envp[i] != NULL)
    {
        new = ft_new_node(envp[i]);
        if (shell->my_envp_h == NULL)
            shell->my_envp_h = new;
        else
            curr->next = new;
        curr = new;
        i++;        
    }
}

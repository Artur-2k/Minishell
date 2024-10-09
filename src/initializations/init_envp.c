/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:37:00 by artuda-s          #+#    #+#             */
/*   Updated: 2024/10/09 18:48:57 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//todo Could add some error checking for malloc on
//todo    str dup, substr and t_envp
//!     Vale a pena checar se envp esta vazio? vai que 
//!     um ninja apaga tudo antes de rodar o minishell xD

static char    *ft_extract_key(char *line)
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

static char    *ft_extract_value(char *line)
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

void    ft_init_envp(t_shell *shell, char *envp[])
{
    int i;

    i = 0;
    while (envp[i])
        i++;
    shell->my_envp = (t_envp*)malloc(sizeof(t_envp) * i + 1);
    i = 0;
    while (envp[i] != NULL)
    {
        shell->my_envp[i].key = ft_extract_key(envp[i]);
        shell->my_envp[i].value = ft_extract_value(envp[i]);
        i++;        
    }
    shell->my_envp[i].key = NULL;
    shell->my_envp[i].value = NULL;
}

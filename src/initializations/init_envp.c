/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:37:00 by artuda-s          #+#    #+#             */
/*   Updated: 2024/11/06 15:47:30 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//todo Could add some error checking for malloc on
//todo    str dup, substr and t_envp
//!     Vale a pena checar se envp esta vazio? vai que
//!     um ninja apaga tudo antes de rodar o minishell xD

/*
 * @brief Recieves the env line and returns its key
 * @return Returns the key or null in case of error
*/
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
			if (!key)
				return (NULL);
            break ;
        }
        else
            end++;
    }
    return (key);
}

/*
 * @brief Recieves the env line and returns its value
 * @return Returns the value or null in case of error
*/
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
			if (!value)
				return (NULL);
            break ;
        }
        start++;
    }
    return (value);
}


/*
 * @brief Allocates memory for a new node and it's key and value
 * @return Returns a pointer to the new node
*/
t_envp   *ft_new_node(char *envp_line)
{
    t_envp  *new_node;

    new_node = (t_envp*)malloc(sizeof(t_envp));
	if (!new_node)
		return (NULL);
    new_node->key = ft_extract_key(envp_line);
	if (!new_node->key)
		return (free(new_node), NULL);
    new_node->value = ft_extract_value(envp_line);
	if (!new_node->value)
		return (free(new_node->key), free(new_node), NULL);
    new_node->next = NULL;
    return (new_node);
}

/*
 * @brief Copies enherited envp to a dynamically allocated
 *      list so we can export and unset new variables
 *      if any allocation fails we free anything allocated and exit
*/
int    ft_init_envp(t_shell *shell, char *envp[])
{
    int 	i;
    t_envp  *curr;
    t_envp  *new;

    curr = NULL;
    i = 0;
    shell->my_envp_h = NULL;
    while (envp && envp[i] != NULL)
    {
        new = ft_new_node(envp[i]);
		if (!new)
			return(ft_free_envp_lst(shell->my_envp_h), 1); // error
        if (shell->my_envp_h == NULL)
            shell->my_envp_h = new;
        else
            curr->next = new;
        curr = new;
        i++;
    }
	return (0); // success
}

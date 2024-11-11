/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:43:27 by artuda-s          #+#    #+#             */
/*   Updated: 2024/11/08 19:59:15 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * @brief Allocates memory for a new node and it's key and value. I KNOW I HAVE
 * THE SAME THING TWICE STFU
 * @return Returns a pointer to the new node
*/
t_envp   *ft_new_env_node(char *key, char *value)
{
    t_envp  *new_node;

    new_node = (t_envp*)malloc(sizeof(t_envp));
	if (!new_node)
		return (NULL);
    new_node->key = ft_strdup(key);
    new_node->value = ft_strdup(value);
    new_node->next = NULL;
    return (new_node);
}

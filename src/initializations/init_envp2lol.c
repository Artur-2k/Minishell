/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp2lol.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:13:55 by artuda-s          #+#    #+#             */
/*   Updated: 2024/11/07 14:15:47 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// vou trocar os contents fuck you nao vou andar a implementar prev agora
static void    ft_swap_node(t_envp *node1, t_envp *node2)
{
    char    *temp;

    // key
    temp = node1->key;
    node1->key = node2->key;
    node2->key = temp;

    //value
    temp = node1->value;
    node1->value = node2->value;
    node2->value = temp;
}

static void    ft_sort_envp2lol(t_shell *shell)
{
    t_envp *i;
    t_envp *j;

    // nothing to sort
    if (!shell->envp2lol_h)
        return ;
    

    //   1 -->  3 --> 5  --> 6   --> NULL    
    /*                      i                  
    *                                 j
     *      
    */
    
   i = shell->envp2lol_h;
   j = i->next;
    
    while (i->next != NULL)
    {
        j = i->next;
        while (j != NULL)
        {
            if (ft_strcmp(i->key, j->key) > 0)
                ft_swap_node(i, j);
            j = j->next;
        }
        i = i->next;
    }
}


/*
 * @brief Same as the one above because im lazy to change code at this point lol 
 *      Copies enherited envp to a dynamically allocated
 *      list so we can export and unset new variables
 *      if any allocation fails we free anything allocated and exit
*/
int    ft_init_envp2lol(t_shell *shell, char *envp[])
{
    int 	i;
    t_envp  *curr;
    t_envp  *new;

    curr = NULL;
    i = 0;
    shell->envp2lol_h = NULL;
    while (envp && envp[i] != NULL)
    {
        new = ft_new_node(envp[i]);
		if (!new)
			return(ft_free_envp_lst(shell->envp2lol_h), 1); // error
        if (shell->envp2lol_h == NULL)
            shell->envp2lol_h = new;
        else
            curr->next = new;
        curr = new;
        i++;
    }
    ft_sort_envp2lol(shell);
	return (0); // success
}

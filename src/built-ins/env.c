/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:03:13 by artuda-s          #+#    #+#             */
/*   Updated: 2024/11/06 15:24:37 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
?   env
!       printa o env por ordem com key=value

?   env asdasd
!       erro de ac safoda xD

*/


/*

*/
void    ft_env(t_exec *cmd)
{
    t_envp *envp;
    
    envp = cmd->shell->my_envp_h;
    while (envp)
    {
        printf("%s=%s\n", envp->key, envp->value);
        envp = envp->next;
    }
}

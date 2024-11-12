/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:45:07 by artuda-s          #+#    #+#             */
/*   Updated: 2024/11/12 21:58:14 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*
?    pwd
!        pwd

?    pwd arg
!        pwd

*unset OLDPWD
?    pwd
!        pwd
 */


void    ft_pwd(t_exec *cmd)
{
    char    *pwd;

    errno = 0;
    pwd = getcwd(NULL, 0);
    if (!pwd)
    {
        ft_what_happened("pwd", strerror(errno));
        cmd->shell->exit_status = 1;
        return ;
    }
    printf("%s\n", pwd);
    free(pwd);
    cmd->shell->exit_status = 0;
}

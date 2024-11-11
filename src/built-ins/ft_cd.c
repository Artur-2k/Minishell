/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:02:41 by artuda-s          #+#    #+#             */
/*   Updated: 2024/11/11 16:36:08 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*


cd /path/absolute    chdir + path

cd relative/path     chdir + path

cd "" // cd ''   stays in place

cd -    -->        OLDPWD ?   cd "$OLDPWD" && pwd  : printf("minihell: cd: OLDPWD not set,sir");

cd      -->        HOME ?   cd "$HOME" && pwd  : printf("minihell: cd: HOME not set,sir");

cd --   -->     HOME ?  muda para $HOME  : printf("minihell: cd: HOME not set,sir");

*/

void    ft_cd(t_exec *cmd)
{
    // cd asdasd asdasd
    if (cmd->av[1] && cmd->av[2])
    {
        ft_what_happened(cmd->av[0], "too many arguments");
        cmd->shell->exit_status = 1;
        return ;
    }

    //       cd                   cd --
    if (!cmd->av[1] || !ft_strcmp(cmd->av[1], "--"))
    {
        if (ft_has_key("HOME", 4, cmd->shell->my_envp_h))
        {
            // OLDPWD set as current directory
            char *curdir = getcwd(NULL, 0);
            ft_set_value("OLDPWD", curdir, cmd->shell->my_envp_h);
            free(curdir);

            // Check HOME value
            char *value = ft_get_value("HOME", cmd->shell->my_envp_h);
            // Same as cd ""
            if (value[0] == '\0')
            {
                cmd->shell->exit_status = 0;
                return ;
            }

            // Change directory to the value
            if (chdir(value) < 0)
            {
                ft_what_happened(cmd->av[0], strerror(errno));
                cmd->shell->exit_status = 1;
                return ;
            }
            // PWD set to home value
            ft_set_value("PWD", value, cmd->shell->my_envp_h);
			return ;
        }
        else
        {
            ft_what_happened(cmd->av[0], "HOME not set,sir");
            cmd->shell->exit_status = 1;
            return ;
        }
    }

    // cd ""
    if (cmd->av[1][0] == '\0')
    {
        cmd->shell->exit_status = 0;
        return ;
    }

    // cd -
    if (ft_strcmp(cmd->av[1], "-") == 0)
    {
        char *oldpwd;
        char *curpwd;

        oldpwd = ft_get_value("OLDPWD", cmd->shell->my_envp_h);
        curpwd = getcwd(NULL, 0);

        if (oldpwd[0] == '\0') // oldpwd == "" || oldpwd not set
        {
            ft_what_happened(cmd->av[0], "OLDPWD not set");
            cmd->shell->exit_status = 1;
            return ;
        }

        // Change directory to the value
        if (chdir(oldpwd) < 0)
        {
            ft_what_happened(cmd->av[0], strerror(errno));
            cmd->shell->exit_status = 1;
            return ;
        }
        // PWD set to home value
        ft_set_value("PWD", oldpwd, cmd->shell->my_envp_h);
        // OLDPWD set to home value
        ft_set_value("OLDPWD", curpwd, cmd->shell->my_envp_h);
        free(curpwd);
        cmd->shell->exit_status = 0;
        return ;
    }

    // cd path
    {
        char *curpwd;

        curpwd = getcwd(NULL, 0);

        // Change directory to the value
        if (chdir(cmd->av[1]) < 0)
        {
            ft_what_happened(cmd->av[1], strerror(errno));
            cmd->shell->exit_status = 1;
            free(curpwd);
            return ;
        }
        // OLDPWD set to home value
        ft_set_value("OLDPWD", curpwd, cmd->shell->my_envp_h);
        free(curpwd);

        curpwd = getcwd(NULL, 0);
        // PWD set to home value
        ft_set_value("PWD", curpwd, cmd->shell->my_envp_h);
        free(curpwd);
        cmd->shell->exit_status = 0;
        return ;
    }
}

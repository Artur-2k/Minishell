/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelo-ca <dmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:02:41 by artuda-s          #+#    #+#             */
/*   Updated: 2024/11/20 15:10:27 by dmelo-ca         ###   ########.fr       */
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

static void	ft_cd_home(t_exec *cmd)
{
	char	*curdir;
	char	*value;

	if (ft_has_key("HOME", 4, cmd->shell->my_envp_h))
    {
        curdir = getcwd(NULL, 0);
        ft_set_value("OLDPWD", curdir, cmd->shell->my_envp_h);
        free(curdir);
        value = ft_get_value("HOME", cmd->shell->my_envp_h);
        if (value[0] == '\0')
            return ;
        if (chdir(value) < 0)
        {
            ft_what_happened(cmd->av[0], strerror(errno));
            cmd->shell->exit_status = 1;
            return ;
        }
        ft_set_value("PWD", value, cmd->shell->my_envp_h);
    }
    else
    {
        ft_what_happened(cmd->av[0], "HOME not set");
        cmd->shell->exit_status = 1;
    }
	return ;
}

static void	ft_cd_old_pwd(t_exec *cmd)
{
    char *oldpwd;
    char *curpwd;

    oldpwd = ft_get_value("OLDPWD", cmd->shell->my_envp_h);
    if (!oldpwd || oldpwd[0] == '\0') // oldpwd == "" || oldpwd not set
    {
        ft_what_happened(cmd->av[0], "OLDPWD not set");
        cmd->shell->exit_status = 1;
        return ;
    }
    curpwd = getcwd(NULL, 0);

    // Change directory to the value
    if (chdir(oldpwd) < 0)
    {
        ft_what_happened(cmd->av[0], strerror(errno));
        cmd->shell->exit_status = 1;
        return ;
    }
    printf("%s\n", oldpwd);
    // PWD set to home value
    ft_set_value("PWD", oldpwd, cmd->shell->my_envp_h);
    // OLDPWD set to home value
    ft_set_value("OLDPWD", curpwd, cmd->shell->my_envp_h);
    free(curpwd);
    return ;
}

static void	ft_cd_path(t_exec *cmd)
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
	return ;
}

void    ft_cd(t_exec *cmd)
{
    cmd->shell->exit_status = 0;

    if (cmd->av[1] && cmd->av[2])							 // cd asdasd asdasd
    {
        ft_what_happened(cmd->av[0], "too many arguments");
        cmd->shell->exit_status = 1;
        return ;
    }
    else if (!cmd->av[1] || !ft_strcmp(cmd->av[1], "--")) 	// cd || cd --
	{
		ft_cd_home(cmd);
		return ;
	}
    else if (cmd->av[1][0] == '\0')  						// cd ""
        return ;
    else if (ft_strcmp(cmd->av[1], "-") == 0)				// cd -
    {
		ft_cd_old_pwd(cmd);
	    return ;
    }
    else 													// cd path
    {
		ft_cd_path(cmd);
        return ;
    }
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:11:14 by artuda-s          #+#    #+#             */
/*   Updated: 2024/11/08 18:20:17 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/**
 * @brief Compares argv to a built in name and if there
 * is a match returns true
*/
bool	ft_is_builtin(t_cmd *cmd)
{
	t_exec	*exec_nd;
	char	*av_zero;

	exec_nd = (t_exec *)cmd;
	av_zero = exec_nd->av[0];
	if (!av_zero)
		return (false);

	if (
			(ft_strcmp(av_zero, "echo") == 0) ||
			(ft_strcmp(av_zero, "cd") == 0) ||
			(ft_strcmp(av_zero, "env") == 0) ||
			(ft_strcmp(av_zero, "export") == 0) ||
			(ft_strcmp(av_zero, "unset") == 0) ||
			(ft_strcmp(av_zero, "pwd") == 0) ||
			(ft_strcmp(av_zero, "exit") == 0)
		)
		return (true);
	return (false);
}

int		ft_redirect_execution(t_exec *cmd)
{
	if (ft_strcmp(cmd->av[0], "echo") == 0)
		ft_echo(cmd);
	else if (ft_strcmp(cmd->av[0], "cd") == 0)
		ft_cd(cmd);
	else if	(ft_strcmp(cmd->av[0], "env") == 0)
		ft_env(cmd);
	else if	(ft_strcmp(cmd->av[0], "export") == 0)
		ft_export(cmd);
	else if	(ft_strcmp(cmd->av[0], "unset") == 0)
		ft_unset(cmd);
	else if	(ft_strcmp(cmd->av[0], "pwd") == 0)
		ft_pwd(cmd);
	else if	(ft_strcmp(cmd->av[0], "exit") == 0)
		ft_exit(cmd);
	return (cmd->shell->exit_status);
}

void	ft_run_builtin(t_exec *cmd)
{
	int	error;
	int	fd_stdin;
	int	fd_stdout;

	fd_stdout = dup(STDOUT_FILENO);
	fd_stdin = dup(STDIN_FILENO);

    // apply redirects
    error = ft_redirects(cmd->redir_list);
    if (error)
	{
		dup2(fd_stdin, STDIN_FILENO);
		dup2(fd_stdout, STDOUT_FILENO);
		close(fd_stdin);
		close(fd_stdout);
		cmd->shell->exit_status = 1;
		return ;
	}

	ft_redirect_execution(cmd);

	dup2(fd_stdin, STDIN_FILENO);
	dup2(fd_stdout, STDOUT_FILENO);
	close(fd_stdin);
	close(fd_stdout);
	return ;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 12:57:38 by artuda-s          #+#    #+#             */
/*   Updated: 2024/10/26 13:23:22 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


static void	ft_redir_stdout(int fd[2])
{
	close(1);
	dup(fd[WRITE_END]);
	close(fd[WRITE_END]);
	close(fd[READ_END]);
}
static void	ft_redir_stdin(int fd[2])
{
    close(0);
    dup(fd[READ_END]);
    close(fd[WRITE_END]);
    close(fd[READ_END]);
}

void	ft_pipe(t_pipe *node, t_shell *shell)
{
    int     fd[2];
	int		pid1;
	int		pid2;

    if (pipe(fd) < 0)
		exit (1); // TODO
	pid1 = fork();
    if (pid1 == 0)
    {
		ft_redir_stdout(fd);
        ft_run_tree((t_cmd *)node->left, shell);
        exit (1);
    }
    pid2 = fork();
	if (pid2 == 0)
	{
		ft_redir_stdin(fd);
	    ft_run_tree((t_cmd *)node->right, shell);
	    exit (1);
	}
    close(fd[WRITE_END]);
    close(fd[READ_END]);
    wait (0);
    wait (0);
	return ;
}

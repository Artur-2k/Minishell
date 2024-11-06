/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 12:57:38 by artuda-s          #+#    #+#             */
/*   Updated: 2024/11/06 14:43:30 by artuda-s         ###   ########.fr       */
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

void    ft_exit_pipe(t_shell *shell)
{
	free(shell->input);
	free (shell->spid);
    free (shell->sexit_status);
	ft_free_tree(shell->cmd_tree);
    ft_free_envp_lst(shell->my_envp_h);
    rl_clear_history();
    exit (EXIT_FAILURE);
}

void	ft_pipe(t_pipe *node, t_shell *shell)
{
    int     fd[2];
	int		pid1;
	int		pid2;

    if (pipe(fd) < 0)
		ft_exit_pipe(shell);
	pid1 = fork();
    if (pid1 == 0)
    {
		ft_redir_stdout(fd);
        ft_run_tree((t_cmd *)node->left, shell);
		ft_exit_pipe(shell);
    }
    pid2 = fork();
	if (pid2 == 0)
	{
		ft_redir_stdin(fd);
	    ft_run_tree((t_cmd *)node->right, shell);
		ft_exit_pipe(shell);
	}
    close(fd[WRITE_END]);
    close(fd[READ_END]);



    int status[2];
    int exit[2];
    
    waitpid (pid1, &status[0], 0);
    waitpid (pid2, &status[1], 0);
    
    if (WIFSIGNALED(status[0]) || WIFSIGNALED(status[1]))
    {
        exit[0] = WTERMSIG(status[0]);  
        exit[1] = WTERMSIG(status[1]);  
        
        if (exit[0] == SIGINT && exit[1] == SIGINT)
            ft_putstr_fd("\n", STDOUT_FILENO);
        if (exit[0] == SIGQUIT && exit[1] ==  SIGQUIT)
            ft_putstr_fd("Quit (core dumped), sir\n", STDOUT_FILENO);
        if (WIFSIGNALED(exit[1]))
            shell->exit_status = 128 + exit[1];
    }
    else
        shell->exit_status = WEXITSTATUS(status[1]);
    return ;
}

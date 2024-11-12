/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 12:57:38 by artuda-s          #+#    #+#             */
/*   Updated: 2024/11/12 21:04:41 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief	Closes fd used for output and uses dup to open a copy of the write
 * end of the pipe to that spot on the table and cleans after it
 */
static void	ft_redir_stdout(int fd[2])
{
	close(STDOUT_FILENO);
	dup(fd[WRITE_END]);
	close(fd[WRITE_END]);
	close(fd[READ_END]);
}

/**
 * @brief	Closes fd used for input and uses dup to open a copy of the read
 * end of the pipe to that spot on the table and cleans after it
 */
static void	ft_redir_stdin(int fd[2])
{
    close(STDIN_FILENO);
    dup(fd[READ_END]);
    close(fd[WRITE_END]);
    close(fd[READ_END]);
}

/**
 * @brief	Dealocates everything allocated and exits with failure status
 */
static void    ft_exit_pipe(t_shell *shell)
{

	free(shell->input);
	free(shell->spid);
    free(shell->sexit_status);
	ft_free_tree(shell->cmd_tree);
    ft_free_envp_lst(shell->my_envp_h);
    ft_free_envp_lst(shell->envp2lol_h); // envp list
    rl_clear_history();
    exit (EXIT_FAILURE);
}

/**
 * @brief	Waits for both childs and checks for the exit condition.
 * If any of them was signaled we act accordingly and if not we fetch
 * the exit status of the last command
 */
static void	ft_wait_n_fetch_status(t_shell *shell, int pid[2])
{
    int	status[2];
    int	exit[2];

    waitpid(pid[0], &status[0], 0);
    waitpid(pid[1], &status[1], 0);
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

/**
 *	@brief	Opens a pipe that will be used to redirect the output of a
 * command to the input of the next. For each command we will fork once
 * and the fetch the exit status.
 */
void	ft_pipe(t_pipe *node, t_shell *shell)
{
    int     fd[2];
	int		pid[2];

	// Opens pipe
    if (pipe(fd) < 0)
		ft_exit_pipe(shell); // Error

	// Child one executes the node to the left
	pid[0] = fork();
    if (pid[0] == 0)
    {
		ft_redir_stdout(fd);
        ft_run_tree((t_cmd *)node->left, shell);
		ft_exit_pipe(shell);
    }

	// Child two keeps executing to the right
    pid[1] = fork();
	if (pid[1] == 0)
	{
		ft_redir_stdin(fd);
	    ft_run_tree((t_cmd *)node->right, shell);
		ft_exit_pipe(shell);
	}
    close(fd[WRITE_END]);
    close(fd[READ_END]);

	// Waits and gets the exit status
	ft_wait_n_fetch_status(shell, pid);
    return ;
}

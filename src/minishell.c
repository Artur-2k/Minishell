/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:33:37 by artuda-s          #+#    #+#             */
/*   Updated: 2024/11/08 17:59:15 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern unsigned char g_signal;

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

	if (	(ft_strcmp(av_zero, "echo") == 0) ||
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

	dup2(fd_stdin, STDIN_FILENO);
	dup2(fd_stdout, STDOUT_FILENO);
	close(fd_stdin);
	close(fd_stdout);
	return ;
}

void    ft_run_cmd(t_shell *shell)
{
    int	pid;

    if (!shell->cmd_tree)
        return ;

	// if there is no pipe and there is a built in it must be ran on main process
	if (shell->cmd_tree->type == EXEC &&
		ft_is_builtin(shell->cmd_tree))
		ft_run_builtin(shell->cmd_tree);

    ft_signal_ignore();
    pid = fork();
    // child doenst return back here it exits
    if (pid == 0)
        ft_run_tree(shell->cmd_tree, shell);


    waitpid(pid, &shell->status, 0);

    if (WIFEXITED(shell->status))
        shell->exit_status = WEXITSTATUS(shell->status);
    else if (WIFSIGNALED(shell->status))
    {
        int signo;
        signo = WTERMSIG(shell->status);
        if (signo == SIGINT)
            ft_putstr_fd("\n", 2);
        else if (signo == SIGQUIT)
            ft_putstr_fd("Quit (core dumped), sir\n", 2);
        shell->exit_status = 128 + signo;
    }

    // Replace exit status
    free(shell->sexit_status);
    shell->sexit_status = ft_itoa(shell->exit_status);

    ft_free_tree(shell->cmd_tree);
    shell->cmd_tree = NULL;
}


int     main(int ac, char** av, char *envp[])
{
    t_shell    shell;


    // dont know if needed but for Wflags
    (void)ac;
    (void)av;


    // init shit
    ft_config_terminal();
    if (ft_init_envp(&shell, envp))
		return (ft_putstr_fd("Malloc error, sir\n", STDERR_FILENO), 1);
    if (ft_init_envp2lol(&shell, envp))
		return (ft_putstr_fd("Malloc error, sir\n", STDERR_FILENO), 1);

    // TODO SHELL INIT
    shell.envp2lol_h = NULL;
    shell.cmd_tree = NULL;
    shell.status = 0;

    shell.exit_status = 0;
    shell.sexit_status = ft_strdup("0");

    shell.pid = ft_get_pid();
    shell.spid = ft_itoa(shell.pid);



    while (true)
    {
        ft_init_signals();
        // Ctrl C
        g_signal = 0;

		// Reads input from user
        shell.input = readline(RED"Minihell => "RES);

        // Ctrl+D (EOF), readline retorna NULL
        if (shell.input == NULL)
            break;

        if (g_signal)
            shell.exit_status = 128 + g_signal;


        // Tokenizes the input and checks for syntax errors
        if (ft_tokenizer(&shell))
        {
            shell.exit_status = 1;
            free(shell.input);
            continue ;
        }

        // This function doesnt need a return statement
        ft_run_cmd(&shell);

        // Verifica se o input não está vazio antes de adicionar ao histórico
	    if (*shell.input != '\0')
            add_history(shell.input);

        free(shell.input); // input
    }

    //release everything
    // envp, tree (! pais e filhos)
    free (shell.spid);
    free (shell.sexit_status);

    ft_free_envp_lst(shell.envp2lol_h); // envp list
    ft_free_envp_lst(shell.my_envp_h); // envp list
    rl_clear_history(); // history
    printf("exit\n");
    return (0);
}

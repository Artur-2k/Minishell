/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:33:37 by artuda-s          #+#    #+#             */
/*   Updated: 2024/11/04 17:04:49 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_run_cmd(t_shell *shell)
{
    int	status;
    int	pid;
    
    if (!shell->cmd_tree)
        return ;
    
    ft_signal_ignore();
    pid = fork();
    // child doenst return back here it exits
    if (pid == 0)
        ft_run_tree(shell->cmd_tree, shell);
    
    
    waitpid(pid, &status, 0);
    
    if (WIFEXITED(status))
        shell->exit_status = WEXITSTATUS(status);
    else if (WTERMSIG(status)){} //TODO signal e tal

    
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
    

    // probably init shell bools and shit
    
    ft_config_terminal();
    if (ft_init_envp(&shell, envp))
		return (ft_putstr_fd("Malloc error, sir\n", STDERR_FILENO), 1);
    
    // TODO SHELL INIT 
    shell.cmd_tree = NULL;
    shell.status = 0;
    
    shell.exit_status = 0;
    shell.sexit_status = ft_strdup("0");
    
    shell.pid = ft_get_pid();
    shell.spid = ft_itoa(shell.pid);


    

    

    while (true)
    {

        ft_init_signals();
		// Reads input from user
        shell.input = readline(RED"Minihell => "RES);

        // Ctrl+D (EOF), readline retorna NULL
        if (shell.input == NULL)
            break;

        // Tokenizes the input and checks for syntax errors
        if (ft_tokenizer(&shell))
        {
            shell.exit_status = 1;
            free(shell.input);
            continue ;
        }
        
        // TODO error checking a partir daqui is missing
        // This function doesnt need a return statement
        ft_run_cmd(&shell);

        // Verifica se o input não está vazio antes de adicionar ao histórico
	    if (*shell.input != '\0')
            add_history(shell.input);

        free(shell.input);
    }

    //release everything
    // envp, tree (! pais e filhos)
    free (shell.spid);
    free (shell.sexit_status);
    
    
    ft_free_envp_lst(shell.my_envp_h);
    rl_clear_history();
    printf("exit\n");
    return (0);
}

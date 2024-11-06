/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:33:37 by artuda-s          #+#    #+#             */
/*   Updated: 2024/11/06 18:15:28 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern unsigned char g_signal;

void    ft_run_cmd(t_shell *shell)
{
    int	pid;
    
    if (!shell->cmd_tree)
        return ;
    
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
        // Ctrl C
        g_signal = 0;

        ft_init_signals();
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

        printf("fiiiiim \n");


        // Verifica se o input não está vazio antes de adicionar ao histórico
	    if (*shell.input != '\0')
            add_history(shell.input);

        free(shell.input); // input
    }

    //release everything
    // envp, tree (! pais e filhos)
    free (shell.spid);
    free (shell.sexit_status);
    
    
    ft_free_envp_lst(shell.my_envp_h); // envp list
    rl_clear_history(); // history
    printf("exit\n");
    return (0);
}

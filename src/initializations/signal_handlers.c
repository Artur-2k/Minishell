/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:22:21 by artuda-s          #+#    #+#             */
/*   Updated: 2024/10/09 14:09:47 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void    ft_handle_sigint(int signo)
{
    (void)signo;
    printf("\n");
    // Notifica o Readline que uma nova linha será iniciada
    rl_on_new_line();
    // Substitui o conteúdo da linha atual por uma linha em branco
    rl_replace_line("", 0);
    // Redesenha o prompt limpo após o sinal
    rl_redisplay();
}
    
void    ft_init_signals(t_shell *shell)
{
    // Ignora o caractere ^C do terminal 
    // Tem de ser configurado antes de poder receber um sinal
    struct termios termios_p;
    tcgetattr(STDIN_FILENO, &termios_p); // reads the config
    termios_p.c_lflag &= ~ECHOCTL; // Nega esta flag para Ctrl+C e Ctrl+D (switch on and off)
    tcsetattr(STDIN_FILENO, TCSANOW, &termios_p); // aplies the new config
    
    // Sigint
    shell->sa_int.sa_handler = ft_handle_sigint;
    shell->sa_int.sa_flags = 0;
    sigemptyset(&shell->sa_int.sa_mask);
    sigaction(SIGINT, &shell->sa_int, NULL);
    
    // Sigquit
    shell->sa_quit.sa_handler = SIG_IGN;
    shell->sa_quit.sa_flags = 0;
    sigemptyset(&shell->sa_quit.sa_mask);
    sigaction(SIGQUIT, &shell->sa_quit, NULL);
}

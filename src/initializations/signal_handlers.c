/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:22:21 by artuda-s          #+#    #+#             */
/*   Updated: 2024/11/08 18:02:50 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned char   g_signal;

void    ft_config_terminal(void)
{
    // Ignora o caractere ^C do terminal
    // Tem de ser configurado antes de poder receber um sinal
    struct termios  termios_p;

    tcgetattr(STDIN_FILENO, &termios_p); // reads the config
    termios_p.c_lflag &= ~ECHOCTL; // Nega esta flag para Ctrl+C e Ctrl+D (switch on and off)
    tcsetattr(STDIN_FILENO, TCSANOW, &termios_p); // aplies the new config
}


/*
 * @brief Removes terminal config to remove control characters print.
*/
static void    ft_handle_sigint(int signo)
{
    g_signal = signo;

    printf("\n");
    // Notifica o Readline que uma nova linha será iniciada
    rl_on_new_line();
    // Substitui o conteúdo da linha atual por uma linha em branco
    rl_replace_line("", 0);
    // Redesenha o prompt limpo após o sinal
    rl_redisplay();
}

/*
 * @brief Utility redefinition on sigint and sigquit.
 * Makes SIGINT clear the line and redisplay prompt.
 * Makes SIGQUIT useless.
*/
void    ft_init_signals(void)
{
    struct sigaction    sa_int;
    struct sigaction    sa_quit;

    // Sigint
    sa_int.sa_handler = ft_handle_sigint;
    sa_int.sa_flags = 0;
    sigemptyset(&sa_int.sa_mask);
    sigaction(SIGINT, &sa_int, NULL);

    // Sigquit
    sa_quit.sa_handler = SIG_IGN;
    sa_quit.sa_flags = 0;
    sigemptyset(&sa_quit.sa_mask);
    sigaction(SIGQUIT, &sa_quit, NULL);
}

void    ft_signal_restore(void)
{
    struct sigaction    sa_dft;

    sa_dft.sa_handler = SIG_DFL;
    sa_dft.sa_flags = 0;
    sigemptyset(&sa_dft.sa_mask);

    sigaction(SIGINT, &sa_dft, NULL);
    sigaction(SIGQUIT, &sa_dft, NULL);
}

// lazy ass didnt want to use sigaction lol
void    ft_signal_ignore(void)
{
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
}
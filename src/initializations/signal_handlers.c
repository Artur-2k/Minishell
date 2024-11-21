/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelo-ca <dmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:22:21 by artuda-s          #+#    #+#             */
/*   Updated: 2024/11/21 14:45:53 by dmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned char	g_signal;

void	ft_config_terminal(void)
{
	struct termios	termios_p;

	tcgetattr(STDIN_FILENO, &termios_p);
	termios_p.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &termios_p);
}

/**
 * @brief Removes terminal config to remove control characters print.
*/
static void	ft_handle_sigint(int signo)
{
	g_signal = signo;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/**
 * @brief Utility redefinition on sigint and sigquit.
 * Makes SIGINT clear the line and redisplay prompt.
 * Makes SIGQUIT useless.
*/
void	ft_init_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = ft_handle_sigint;
	sa_int.sa_flags = 0;
	sigemptyset(&sa_int.sa_mask);
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = 0;
	sigemptyset(&sa_quit.sa_mask);
	sigaction(SIGQUIT, &sa_quit, NULL);
}

/**
 * @brief Utility restoration on sigint and sigquit.
*/
void	ft_signal_restore(void)
{
	struct sigaction	sa_dft;

	sa_dft.sa_handler = SIG_DFL;
	sa_dft.sa_flags = 0;
	sigemptyset(&sa_dft.sa_mask);
	sigaction(SIGINT, &sa_dft, NULL);
	sigaction(SIGQUIT, &sa_dft, NULL);
}

// lazy ass didnt want to use sigaction lol
void	ft_signal_ignore(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

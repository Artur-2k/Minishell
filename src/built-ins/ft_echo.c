/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:01:42 by artuda-s          #+#    #+#             */
/*   Updated: 2024/11/06 18:30:37 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// av[0] echo
// av[1] -n
// av[2] -nnn
// av[3] -nasd
// av[4] ola
// av[3] mundo
// av[3] NULL
/*
echo -n ola mundo
ola mundoartur@Artur:~$

artur@Artur:~$ echo -nnnn ola mundo
ola mundoartur@Artur:~$

artur@Artur:~$ echo -nnnn -n ola mundo
ola mundoartur@Artur:~$

artur@Artur:~$ echo -nnnn -nnnnnn  ola mundo
ola mundoartur@Artur:~$ echo -nnnn -nnnnnn  ola mundo

artur@Artur:~$ echo -nnnn -nnnnnna  ola mundo
-nnnnnna ola mundoartur@Artur:~$

artur@Artur:~$ echo -nnnn -nnnnnn  ola -n mundo
ola -n mundoartur@Artur:~$

artur@Artur:~$ echo --n ola mundo
--n ola mundo

echo -n

doenst do anything
*/

/**
 * @brief Simple echo that only had the -n flag
 * @param cmd Echo command (we need the argv)
 * @retval None
*/
void	ft_echo(t_exec *cmd)
{
	bool	nlflag;
	int		i;
	int		j;

	nlflag = true;
	i = 1;
	while (cmd->av[i] && cmd->av[i][0] == '-')
	{
		j = 1;
		while (cmd->av[i][j] == 'n')
			j++;
		if (cmd->av[i][j])
			break;
		nlflag = false;
		i++;
	}
	while (cmd->av[i])
	{
		ft_putstr_fd(cmd->av[i], 1);
		if (cmd->av[++i])
			write(1, " ", 1);
	}
	if (nlflag)
		write(1, "\n", 1);
	cmd->shell->exit_status = 0;
}

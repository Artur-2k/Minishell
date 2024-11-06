/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:26:40 by artuda-s          #+#    #+#             */
/*   Updated: 2024/11/06 10:03:41 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* exit
! printa exit
!    exits with 0

* exit (unsigned char)
! printa exit
! 	exits with (unsigned char)

* exit (unsigned char) ...
!printa exit
!	printa exit: demasiados argumentos
!		sets exit status to 1

* exit (nondigit) ....
! printa exit
!	printa bash: exit: asdasdaasd: requer um argumento numérico
!		exits with status to 2

*/

static void	ft_str_digits(t_exec *cmd)
{
	int	i;

	i = 0;
	if (!cmd->av[1][i])
	{
		//TODO free all
		printf("Minihell: exit: %s: numeric argument required, sir\n", cmd->av[1]);
		exit (2);
	}
	while (cmd->av[1][i])
	{
		if (!ft_isdigit(cmd->av[1][i])) // exit 12abc (asdasd)
		{
			//TODO free all
			printf("Minihell: exit: %s: numeric argument required, sir\n", cmd->av[1]);
			exit (2);
		}
		i++;
	}
}

void	ft_exit(t_exec *cmd)
{
	// Always prints exit for some reason
	printf("exit\n");

	// Exit no args
	if (cmd->av[1] == NULL)
	{
		//TODO free all
		exit (EXIT_SUCCESS);
	}

	// Check for only digits on av[1]
	ft_str_digits(cmd); // this function exits on bad input

	printf("ola\n");
	// Exit with args
	if (cmd->av[2] == NULL) // exit 5
	{
		//TODO free all
		exit ((unsigned char)ft_atoi(cmd->av[1]));
	}
	else // exit 5 asdasd
	{
		printf("Minihell: exit: too many arguments, sir\n");
		cmd->shell->exit_status = 1;
		return ;
	}
}

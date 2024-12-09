/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:26:40 by artuda-s          #+#    #+#             */
/*   Updated: 2024/12/09 17:41:52 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define MY_LONG_MAX "9223372036854775807"
#define MY_LONG_MIN "9223372036854775808"

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

static void	ft_exit_error_print(char *av1, char *error)
{
	ft_putstr_fd("Minihell: exit: ", 2);
	ft_putstr_fd(av1, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd(", sir\n", 2);
}

static void	ft_clean(t_shell *shell)
{
	free(shell->input);
	free (shell->spid);
	free (shell->sexit_status);
	ft_free_tree(shell->cmd_tree);
	ft_free_envp_lst(shell->my_envp_h);
	ft_free_envp_lst(shell->envp2lol_h);
	rl_clear_history();
}

static void	ft_str_digits(t_exec *cmd)
{
	int	i;

	i = 0;
	if (!cmd->av[1][i])
	{
		ft_exit_error_print(cmd->av[1], "numeric argument required");
		ft_clean(cmd->shell);
		exit (2);
	}
	if (cmd->av[1][i] == '+' || cmd->av[1][i] == '-')
		i++;
	while (cmd->av[1][i])
	{
		if (!ft_isdigit(cmd->av[1][i]))
		{
			ft_exit_error_print(cmd->av[1], "numeric argument required");
			ft_clean(cmd->shell);
			exit (2);
		}
		i++;
	}
}

static void	ft_check_number_range(t_exec *cmd, char *str)
{
	int	len;

	if (*str == '+' || *str == '-')
		str++;
	len = ft_strlen(str);
	if (len > 19)
	{
		ft_exit_error_print(str, "numeric argument required");
		ft_clean(cmd->shell);
		exit (2);
	}
	if (len == 19)
	{
		if ((cmd->av[1][0] != '-' && ft_strncmp(str, MY_LONG_MAX, 19) > 0) \
		|| (cmd->av[1][0] == '-' && ft_strncmp(str, MY_LONG_MIN, 19) > 0))
		{
			ft_exit_error_print(str, "numeric argument required");
			ft_clean(cmd->shell);
			exit (2);
		}
	}
}

void	ft_exit(t_exec *cmd)
{
	long	exit_code;

	printf("exit\n");
	if (cmd->av[1] == NULL)
	{
		ft_clean(cmd->shell);
		exit (EXIT_SUCCESS);
	}
	ft_str_digits(cmd);
	if (cmd->av[2] == NULL)
	{
		ft_check_number_range(cmd, cmd->av[1]);
		exit_code = (unsigned char)ft_atol(cmd->av[1]);
		ft_clean(cmd->shell);
		exit (exit_code);
	}
	else
	{
		ft_exit_error_print("", "too many arguments");
		if (cmd->shell->exit_status == 0)
			cmd->shell->exit_status = 1;
		return ;
	}
}

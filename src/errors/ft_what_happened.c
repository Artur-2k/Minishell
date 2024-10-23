/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_what_happened.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 20:54:52 by artuda-s          #+#    #+#             */
/*   Updated: 2024/10/23 21:31:47 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * @brief Outputs what happened xD
 * @param what What is the string that made something explode
 * @param happened Happened the string associated to the errno
 * @return Nothing
*/
void	ft_what_happened(char *what, char *happend)
{
	ft_putstr_fd(what, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(happend, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}
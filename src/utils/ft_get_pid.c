/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_pid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:29:42 by artuda-s          #+#    #+#             */
/*   Updated: 2024/12/10 19:18:12 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// returns pid or a < 0 number on error
int	ft_get_pid(void)
{
	int		pid;
	int		fd;
	int		bytes_read;
	char	buffer[50];

	fd = open("/proc/self/stat", O_RDONLY);
	if (fd < 0)
		return (-1);
	bytes_read = read(fd, buffer, sizeof(buffer));
	if (bytes_read < 0)
		return (-2);
	buffer[bytes_read -1] = '\0';
	pid = ft_atoi(buffer);
	close(fd);
	return (pid);
}

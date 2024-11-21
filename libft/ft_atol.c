/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 22:53:55 by artuda-s          #+#    #+#             */
/*   Updated: 2024/11/21 15:47:02 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	ft_choose_one(long sign)
{
	errno = ERANGE;
	if (sign == 1)
		return (LONG_MAX);
	else
		return (LONG_MIN);
}

long	ft_atol(const char *str)
{
	long	result;
	long	sign;

	result = 0;
	sign = 1;
	while (ft_strchr("\t\v\n\f\r ", *str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str && '0' <= *str && *str <= '9')
	{
		if (result > (LONG_MAX - (*str - '0')) / 10)
			return (ft_choose_one(sign));
		result = result * 10 + *str - 48;
		str++;
	}
	return (result * sign);
}

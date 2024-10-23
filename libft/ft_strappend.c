/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:42:29 by artuda-s          #+#    #+#             */
/*   Updated: 2024/10/23 14:23:03 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strappend(char *s1, char *s2)
{
	char	*nstr;
	int		i;
	int		j;

	nstr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!nstr)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		nstr[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
		nstr[i++] = s2[j++];
	nstr[i] = 0;
	if (s1)
		free(s1);
	return (nstr);
}
/*
#include <stdio.h>

int	main(void)
{
	const char *s1 = "ola ";
	const char *s2 = "mundo!";
	char *result = ft_strjoin(s1, s2);
	printf("%s\n", result);
	free(result);
	return (0);
} */
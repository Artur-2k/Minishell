/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_char_to_str.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelo-ca <dmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:01:08 by artuda-s          #+#    #+#             */
/*   Updated: 2024/11/18 16:02:34 by dmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Appends a char to a string keeping it null terminated.
// Returns a new allocated string and frees the old one.
char	*ft_append_char_to_str(char *str, char c)
{
	char	*nstr;
	size_t	len;

	len = 0;
	if (str)
		len = ft_strlen((const char *)str);
	nstr = (char *)malloc(sizeof(char) * len + 2);
	if (!nstr)
		return (errno = 1, free(str), NULL);
	len = 0;
	while (str && str[len])
	{
		nstr[len] = str[len];
		len++;
	}
	nstr[len] = c;
	nstr[++len] = '\0';
	if (str)
		free(str);
	return (nstr);
}

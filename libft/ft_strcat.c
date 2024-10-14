#include "libft.h"

char	*ft_strcat(char *dest, char *src)
{
	int	i;

	i = 0;
	while (dest[i])
		i++;
	while (*src)
	{
		dest[i++] = *src;
		src++;
	}
	dest[i] = 0;
	return dest;
}
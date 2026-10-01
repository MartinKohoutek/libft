#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const unsigned char	*e;

	e = (const unsigned char *)s;
	while (*e)
		e++;
	while (e > (const unsigned char *)s)
	{
		if (*e == (unsigned char)c)
			return ((char *)e);
		e--;
	}
	if (*e == (unsigned char)c)
		return ((char *)e);
	return (NULL);
}

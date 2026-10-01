#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char	*res;
	char	*p;

	if (!s || !f)
		return (NULL);
	res = malloc(ft_strlen(s) + 1);
	if (!res)
		return (NULL);
	p = res;
	while (*s)
	{
		*p = f((unsigned int)(p - res), *s++);
		p++;
	}
	*p = '\0';
	return (res);
}

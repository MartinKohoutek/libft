#include "libft.h"
#include <stdlib.h>

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char		*res;
	char		*p;
	const char	*e;

	if (!s)
		return (NULL);
	while (*s && start--)
		s++;
	e = s;
	while (*e && len--)
		e++;
	res = malloc(e - s + 1);
	if (!res)
		return (NULL);
	p = res;
	while (s < e)
		*p++ = *s++;
	*p = '\0';
	return (res);
}

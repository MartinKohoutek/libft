#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	char	*p;

	if (!f || !s)
		return ;
	p = s;
	while (*p)
	{
		f((unsigned int)(p - s), p);
		p++;
	}
}

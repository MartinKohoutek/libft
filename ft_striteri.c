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

// #include <stdio.h>

// static void	to_upper(unsigned int i, char *c)
// {
// 	(void)i;
// 	*c = ft_toupper(*c);
// }

// int	main(void)
// {
// 	char	str[] = "Hello, World! 42";

// 	printf("Before: %s\n", str);
// 	ft_striteri(str, to_upper);
// 	printf("After:  %s\n", str);
// 	return (0);
// }

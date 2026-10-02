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

// #include <stdio.h>

// static char	to_upper(unsigned int i, char c)
// {
// 	(void)i;
// 	return (ft_toupper(c));
// }

// int	main(void)
// {
// 	char	*str;

// 	str = ft_strmapi("Hello, World! 42", to_upper);
// 	printf("Result: %s\n", str);
// 	free(str);
// 	return (0);
// }
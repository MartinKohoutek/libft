#include "libft.h"

int	ft_atoi(const char *s)
{
	int	sign;
	int	res;

	res = 0;
	sign = 1;
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '-' || *s == '+')
		sign = 1 - 2 * (*s++ == '-');
	while (*s >= '0' && *s <= '9')
		res = res * 10 + *s++ - '0';
	return (res * sign);
}

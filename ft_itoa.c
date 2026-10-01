#include "libft.h"
#include <stdlib.h>
#include <limits.h>

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		tmp;
	int		sign;

	sign = (n < 0);
	len = (n <= 0);
	tmp = n;
	while (tmp)
	{
		tmp /= 10;
		len++;
	}
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	str[0] = '-';
	while (len-- > sign)
	{
		str[len] = ((n % 10) + ((n % 10) < 0) * -2 * (n % 10)) + '0';
		n /= 10;
	}
	return (str);
}

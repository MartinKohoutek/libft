#include "libft.h"

int	ft_isdigit(int c)
{
	return ((unsigned)c - '0' <= 9U);
}

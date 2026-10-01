#include "libft.h"

int	ft_isprint(int c)
{
	return ((unsigned)c - ' ' <= 94U);
}

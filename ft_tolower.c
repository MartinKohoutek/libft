#include "libft.h"

int	ft_tolower(int c)
{
	return (c | (((unsigned)c - 'A' < 26U) * 0x20));
}

#include "libft.h"

int	ft_toupper(int c)
{
	return (c & ~(((unsigned)c - 'a' < 26U) * 0x20));
}

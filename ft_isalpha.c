#include "libft.h"

int	ft_isalpha(int c)
{
	return (((unsigned)c & ~0x20) - 'A' < 26U);
}

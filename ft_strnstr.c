#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	llen;

	llen = ft_strlen(little);
	if (!*little)
		return ((char *)big);
	while (*big && len >= llen)
	{
		if (!ft_strncmp(big, little, llen))
			return ((char *)big);
		big++;
		len--;
	}
	return (NULL);
}

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;

	len = ft_strlen(s) + 1;
	while (len--)
		if ((unsigned char)s[len] == (unsigned char)c)
			return ((char *)&s[len]);
	return (NULL);
}

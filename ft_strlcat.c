#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	slen;
	size_t	dlen;

	slen = ft_strlen(src);
	dlen = ft_strlen(dst);
	if (size <= dlen)
		return (size + slen);
	dst += dlen;
	size = size - dlen - 1;
	while (*src && size--)
		*dst++ = *src++;
	*dst = '\0';
	return (dlen + slen);
}

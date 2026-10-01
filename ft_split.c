#include "libft.h"
#include <stdlib.h>

static size_t	ft_count_words(const char *s, char c)
{
	size_t		count;
	const char	*p;

	count = 0;
	p = s;
	while (*p)
		count += (*p++ != c) && (p - 1 == s || *(p - 2) == c);
	return (count);
}

static int	ft_add_word(char **res, int i, const char *s, const char *e)
{
	res[i] = ft_substr(s, 0, e - s);
	if (!res[i])
	{
		while (i)
			free(res[--i]);
		free(res);
		return (0);
	}
	return (1);
}

char	**ft_split(const char *s, char c)
{
	char		**res;
	const char	*start;
	size_t		i;

	if (!s)
		return (NULL);
	res = malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (!*s)
			break ;
		start = s;
		while (*s && *s != c)
			s++;
		if (!ft_add_word(res, i, start, s))
			return (NULL);
		i++;
	}
	res[i] = NULL;
	return (res);
}

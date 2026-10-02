#include "libft.h"
#include <stdlib.h>

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}

// #include <stdio.h>
// #include <stdlib.h>

// int	main(void)
// {
// 	t_list	*node;
// 	char	*content;

// 	content = malloc(6);
// 	if (!content)
// 		return (1);
// 	ft_strlcpy(content, "Hello", 6);
// 	node = ft_lstnew(content);
// 	if (!node)
// 	{
// 		free(content);
// 		return (1);
// 	}
// 	printf("Before: %s\n", (char *)node->content);
// 	ft_delone(node, free);
// 	printf("Node deleted.\n");
// 	return (0);
// }

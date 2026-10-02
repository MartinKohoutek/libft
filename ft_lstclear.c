#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		next = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = next;
	}
}

// #include <stdio.h>
// #include <stdlib.h>

// int	main(void)
// {
// 	t_list	*lst;
// 	t_list	*node;

// 	lst = ft_lstnew(ft_strdup("One"));
// 	lst->next = ft_lstnew(ft_strdup("Two"));
// 	lst->next->next = ft_lstnew(ft_strdup("Three"));

// 	printf("Before clear:\n");
// 	node = lst;
// 	while (node)
// 	{
// 		printf("%s\n", (char *)node->content);
// 		node = node->next;
// 	}

// 	ft_lstclear(&lst, free);

// 	printf("After clear: %s\n", lst ? "NOT NULL" : "NULL");
// 	return (0);
// }

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

// #include <stdio.h>
// #include <stdlib.h>

// static void	print_content(void *content)
// {
// 	printf("%s\n", (char *)content);
// }

// int	main(void)
// {
// 	t_list	*lst;

// 	lst = ft_lstnew("Hello");
// 	lst->next = ft_lstnew("World");
// 	lst->next->next = ft_lstnew("Libft");

// 	printf("List:\n");
// 	ft_lstiter(lst, print_content);
// 	return (0);
// }
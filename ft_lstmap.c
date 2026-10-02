#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*tmp;
	void	*content;

	if (!f || !del)
		return (NULL);
	new = NULL;
	while (lst)
	{
		content = f(lst->content);
		tmp = ft_lstnew(content);
		if (!tmp)
		{
			del(content);
			ft_lstclear(&new, del);
			return (NULL);
		}
		ft_lstadd_back(&new, tmp);
		lst = lst->next;
	}
	return (new);
}

// static void	*to_upper(void *content)
// {
// 	char	*s;
// 	char	*res;

// 	s = content;
// 	res = ft_strdup(s);
// 	if (!res)
// 		return (NULL);
// 	while (*res)
// 	{
// 		*res = ft_toupper(*res);
// 		res++;
// 	}
// 	return (res - ft_strlen(s));
// }

// static void	del(void *content)
// {
// 	free(content);
// }

// static void	print_content(void *content)
// {
// 	printf("%s\n", (char *)content);
// }

// int	main(void)
// {
// 	t_list	*lst;
// 	t_list	*new;

// 	lst = ft_lstnew(ft_strdup("hello"));
// 	lst->next = ft_lstnew(ft_strdup("world"));
// 	lst->next->next = ft_lstnew(ft_strdup("libft"));
// 	new = ft_lstmap(lst, to_upper, del);
// 	printf("Original:\n");
// 	ft_lstiter(lst, print_content);
// 	printf("Mapped:\n");
// 	ft_lstiter(new, print_content);
// 	ft_lstclear(&lst, del);
// 	ft_lstclear(&new, del);
// 	return (0);
// }

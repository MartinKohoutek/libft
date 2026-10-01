#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdlib.h>
#include "libft.h"

#define LARGE_LIST_SIZE 1000

static void test_empty(void **state)
{
	t_list	*lst = NULL;

	(void)state;
	assert_null(ft_lstlast(lst));
}

static void test_one(void **state)
{
	t_list	*lst = ft_lstnew("A");

	(void)state;
	assert_ptr_equal(ft_lstlast(lst), lst);

	free(lst);
}

static void test_three(void **state)
{
	t_list	*lst 	= ft_lstnew("A");
	lst->next		= ft_lstnew("B");
	lst->next->next	= ft_lstnew("C");

	(void)state;
	assert_ptr_equal(ft_lstlast(lst), lst->next->next);

	free(lst->next->next);
	free(lst->next);
	free(lst);
}

static void test_large(void **state)
{
	t_list	*lst = ft_lstnew(NULL);
	t_list	*last = lst;
	int		i;

	(void)state;
	i = 1;
	while (i < LARGE_LIST_SIZE)
	{
		last->next = ft_lstnew(NULL);
		last = last->next;
		i++;
	}

	assert_ptr_equal(ft_lstlast(lst), last);

	while (lst)
	{
		last = lst->next;
		free(lst);
		lst = last;
	}
}

int main(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_empty),
		cmocka_unit_test(test_one),
		cmocka_unit_test(test_three),
		cmocka_unit_test(test_large),
	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}
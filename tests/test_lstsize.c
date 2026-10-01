#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdlib.h>
#include "libft.h"

#define LARGE_LIST_SIZE	1000

static void test_empty(void **state)
{
	t_list	*lst = NULL;

	(void)state;
	assert_int_equal(ft_lstsize(lst), 0);
}

static void test_one(void **state)
{
	t_list	*lst = ft_lstnew("A");

	(void)state;
	assert_int_equal(ft_lstsize(lst), 1);

	free(lst);
}

static void test_three(void **state)
{
	t_list	*lst	= ft_lstnew("A");
	lst->next	 	= ft_lstnew("B");
	lst->next->next = ft_lstnew("C");

	(void)state;
	assert_int_equal(ft_lstsize(lst), 3);

	free(lst->next->next);
	free(lst->next);
	free(lst);
}

static void test_large(void **state)
{
	t_list	*lst = NULL;
	t_list	*node;
	int		i;

	(void)state;
	i = 0;
	while (i < LARGE_LIST_SIZE)
	{
		node = ft_lstnew(NULL);
		node->next = lst;
		lst = node;
		i++;
	}

	assert_int_equal(ft_lstsize(lst), LARGE_LIST_SIZE);

	while (lst)
	{
		node = lst->next;
		free(lst);
		lst = node;
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
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
	t_list	*new = ft_lstnew("X");

	(void)state;
	ft_lstadd_back(&lst, new);

	assert_ptr_equal(lst, new);
	assert_ptr_equal(lst->content, "X");
	assert_null(lst->next);

	free(lst);
}

static void test_one(void **state)
{
	t_list	*lst = ft_lstnew("A");
	t_list	*new = ft_lstnew("B");

	(void)state;
	ft_lstadd_back(&lst, new);

	assert_ptr_equal(lst->next, new);
	assert_ptr_equal(lst->next->content, "B");
	assert_null(lst->next->next);

	free(lst->next);
	free(lst);
}

static void test_three(void **state)
{
	t_list	*lst 	= ft_lstnew("A");
	lst->next	 	= ft_lstnew("B");
	lst->next->next = ft_lstnew("C");
	t_list	*new	= ft_lstnew("D");

	(void)state;
	ft_lstadd_back(&lst, new);

	assert_ptr_equal(lst->next->next->next, new);
	assert_ptr_equal(new->content, "D");
	assert_null(new->next);

	free(lst->next->next->next);
	free(lst->next->next);
	free(lst->next);
	free(lst);
}

// new = null => lst se nezmeni
static void test_new_null(void **state)
{
	t_list	*lst = ft_lstnew("A");
	t_list	*old = lst;

	(void)state;
	ft_lstadd_back(&lst, NULL);

	assert_ptr_equal(lst, old);
	assert_ptr_equal(lst->content, "A");
	assert_null(lst->next);

	free(lst);
}

// new se nezmeni
static void test_lst_null(void **state)
{
	t_list	*new = ft_lstnew("X");

	(void)state;
	ft_lstadd_back(NULL, new);

	assert_ptr_equal(new->content, "X");
	assert_null(new->next);

	free(new);
}

static void test_large(void **state)
{
	t_list	*lst	= ft_lstnew(NULL);
	t_list	*last	= lst;
	t_list	*new;
	int 	i;

	(void)state;
	i = 1;
	while (i < LARGE_LIST_SIZE)
	{
		last->next = ft_lstnew(NULL);
		last = last->next;
		i++;
	}

	new = ft_lstnew("X");
	ft_lstadd_back(&lst, new);

	assert_ptr_equal(last->next, new);
	assert_null(new->next);

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
		cmocka_unit_test(test_new_null),
		cmocka_unit_test(test_lst_null),
		cmocka_unit_test(test_large),
	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include <stdlib.h>
#include "libft.h"

static void test_basic(void **state)
{
	t_list	*lst = ft_lstnew("A");
	lst->next 	 = ft_lstnew("B");
	t_list	*new = ft_lstnew("X");

	(void)state;
	ft_lstadd_front(&lst, new);

	assert_ptr_equal(lst, new);
	assert_ptr_equal(lst->content, "X");
	assert_ptr_equal(lst->next->content, "A");
	assert_ptr_equal(lst->next->next->content, "B");
	assert_null(lst->next->next->next);

	free(lst->next->next);
	free(lst->next);
	free(lst);
}

static void test_empty_list(void **state)
{
	t_list	*lst = NULL;
	t_list	*new = ft_lstnew("X");

	(void)state;
	ft_lstadd_front(&lst, new);

	assert_ptr_equal(lst, new);
	assert_ptr_equal(lst->content, "X");
	assert_null(lst->next);

	free(lst);
}

// je-le new = NULL, lst se nesmi zmenit
static void test_new_null(void **state)
{
	t_list	*lst = ft_lstnew("A");
	t_list	*old = lst;

	(void)state;
	ft_lstadd_front(&lst, NULL);

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
	ft_lstadd_front(NULL, new);

	assert_ptr_equal(new->content, "X");
	assert_null(new->next);

	free(new);
}

int main(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_basic),
		cmocka_unit_test(test_empty_list),
		cmocka_unit_test(test_new_null),
		cmocka_unit_test(test_lst_null),
	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}
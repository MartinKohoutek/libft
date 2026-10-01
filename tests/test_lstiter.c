#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include <stdlib.h>
#include "libft.h"

#define LIST_SIZE 1000

static int call_count;
static void *called_content[LIST_SIZE];

static void callback(void *content)
{
	called_content[call_count++] = content;
} 

static void test_empty(void **state)
{
	t_list *lst = NULL;

	(void)state;
	call_count = 0;

	ft_lstiter(lst, callback);

	assert_int_equal(call_count, 0);
}

static void test_one(void **state)
{
	char	*content = "A";
	t_list	*lst 	 = ft_lstnew(content);

	(void)state;
	call_count = 0;

	ft_lstiter(lst, callback);

	assert_int_equal(call_count, 1);
	assert_ptr_equal(called_content[0], content);

	free(lst);
}

static void test_three(void **state)
{
	t_list	*lst	= ft_lstnew("A");
	t_list	*node2	= ft_lstnew("B");
	t_list	*node3	= ft_lstnew("C");
	t_list	*first	= lst;

	(void)state;
	lst->next = node2;
	node2->next = node3;

	call_count = 0;

	ft_lstiter(lst, callback);

	assert_int_equal(call_count, 3);
	assert_ptr_equal(called_content[0], "A");
	assert_ptr_equal(called_content[1], "B");
	assert_ptr_equal(called_content[2], "C");

	assert_ptr_equal(lst, first);
	assert_ptr_equal(lst->next, node2);
	assert_ptr_equal(lst->next->next, node3);
	assert_null(lst->next->next->next);

	free(node3);
	free(node2);
	free(lst);
}

static void test_large(void **state)
{
	t_list	*lst	= ft_lstnew(NULL);
	t_list	*node	= lst;
	int		i;

	(void)state;
	i = 1;
	while (i < LIST_SIZE)
	{
		node->next = ft_lstnew(NULL);
		node = node->next;
		i++;
	}

	call_count = 0;

	ft_lstiter(lst, callback);

	assert_int_equal(call_count, LIST_SIZE);

	while (lst)
	{
		node = lst->next;
		free(lst);
		lst = node;
	}
}

static void test_null_callback(void **state)
{
	t_list	*lst 	= ft_lstnew("A");
	t_list	*node 	= lst;

	(void)state;
	call_count = 0;

	ft_lstiter(lst, NULL);

	assert_int_equal(call_count, 0);
	assert_ptr_equal(lst, node);
	assert_null(lst->next);

	free(lst);
}

int main(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_empty),
		cmocka_unit_test(test_one),
		cmocka_unit_test(test_three),
		cmocka_unit_test(test_large),
		cmocka_unit_test(test_null_callback),
	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}
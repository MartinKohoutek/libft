#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include <stdlib.h>
#include "libft.h"

#define LIST_SIZE 1000

static void *mapped_content[3] = {"X", "Y", "Z"};
static int map_count;

static void *map_callback(void *content)
{
	(void)content;
	return (mapped_content[map_count++]);
}

static void del_callback(void *content)
{
	(void)content;
}

static void test_one(void **state)
{
	t_list	*lst = ft_lstnew("A");
	t_list	*res = ft_lstmap(lst, map_callback, del_callback);

	(void)state;
	map_count = 0;

	assert_non_null(res);
	assert_ptr_equal(res->content, "X");
	assert_null(res->next);

	assert_ptr_equal(lst->content, "A");
	assert_null(lst->next);

	free(res);
	free(lst);
}

static void test_three(void **state)
{
	t_list	*lst	= ft_lstnew("A");
	t_list	*node2	= ft_lstnew("B");
	t_list	*node3	= ft_lstnew("C");
	t_list	*res;

	(void)state;
	lst->next = node2;
	node2->next = node3;

	map_count = 0;

	res = ft_lstmap(lst, map_callback, del_callback);

	assert_non_null(res);
	assert_ptr_equal(res->content, "X");
	assert_ptr_equal(res->next->content, "Y");
	assert_ptr_equal(res->next->next->content, "Z");
	assert_null(res->next->next->next);

	assert_ptr_equal(lst->content, "A");
	assert_ptr_equal(lst->next, node2);
	assert_ptr_equal(node2->next, node3);
	assert_null(node3->next);

	free(res->next->next);
	free(res->next);
	free(res);

	free(node3);
	free(node2);
	free(lst);
}

static void test_empty_lst(void **state)
{
	t_list	*res;

	(void)state;
	res = ft_lstmap(NULL, map_callback, del_callback);
	assert_null(res);
}

static void test_null_f(void **state)
{
	t_list	*lst	= ft_lstnew("A");
	t_list	*res;

	(void)state;
	res = ft_lstmap(lst, NULL, del_callback);

	assert_null(res);

	assert_ptr_equal(lst->content, "A");
	assert_null(lst->next);

	free(lst);
}

static void test_null_del(void **state)
{
	t_list	*lst	= ft_lstnew("A");
	t_list	*res;

	(void)state;
	res = ft_lstmap(lst, map_callback, NULL);

	assert_null(res);
	assert_ptr_equal(lst->content, "A");
	assert_null(lst->next);

	free (lst);
}

int main(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_one),
		cmocka_unit_test(test_three),
		cmocka_unit_test(test_empty_lst),
		cmocka_unit_test(test_null_f),
		cmocka_unit_test(test_null_del),
	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}
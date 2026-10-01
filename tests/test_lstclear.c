#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include <stdlib.h>
#include "libft.h"

#define LIST_SIZE 1000

static int spy_free;
static void *deleted_content[LIST_SIZE];
static void *freed_ptr[LIST_SIZE];
static int del_count;
static int free_count;

void __real_free(void *ptr);
void __wrap_free(void *ptr)
{
	if (spy_free)
		freed_ptr[free_count++] = ptr;
	__real_free(ptr);
}

static void del_wrapped(void *content)
{
	deleted_content[del_count++] = content;
}

static void reset_spies(void)
{
	memset(deleted_content, 0, sizeof(deleted_content));
	memset(freed_ptr, 0, sizeof(freed_ptr));
	del_count = 0;
	free_count = 0;
}

static void test_empty(void **state)
{
	t_list	*lst = NULL;

	(void)state;
	reset_spies();	

	spy_free = 1;
	ft_lstclear(&lst, del_wrapped);
	spy_free = 0;

	assert_null(lst);
	assert_int_equal(del_count, 0);
	assert_int_equal(free_count, 0);
}

static void test_one(void **state)
{
	t_list	*lst  = ft_lstnew("A");
	t_list	*node = lst;

	(void)state;
	reset_spies();

	spy_free = 1;
	ft_lstclear(&lst, del_wrapped);
	spy_free = 0;

	assert_null(lst);
	assert_int_equal(del_count, 1);
	assert_int_equal(free_count, 1);
	assert_ptr_equal(deleted_content[0], "A");
	assert_ptr_equal(freed_ptr[0], node);
}

static void test_three(void **state)
{
	t_list	*lst 	= ft_lstnew("A");
	t_list	*node1  = lst;
	t_list	*node2	= ft_lstnew("B");
	t_list	*node3	= ft_lstnew("C");

	(void)state;
	lst->next = node2;
	lst->next->next = node3;

	reset_spies();

	spy_free = 1;
	ft_lstclear(&lst, del_wrapped);
	spy_free = 0;

	assert_null(lst);
	assert_int_equal(del_count, 3);
	assert_int_equal(free_count, 3);

	assert_ptr_equal(deleted_content[0], "A");
	assert_ptr_equal(deleted_content[1], "B");
	assert_ptr_equal(deleted_content[2], "C");

	assert_ptr_equal(freed_ptr[0], node1);
	assert_ptr_equal(freed_ptr[1], node2);
	assert_ptr_equal(freed_ptr[2], node3);
}

static void test_null_del(void **state)
{
	t_list	*lst	= ft_lstnew("A");
	t_list	*node	= ft_lstnew("B");
	t_list	*first	= lst;

	(void)state;
	lst->next = node;

	reset_spies();

	spy_free = 1;
	ft_lstclear(&lst, NULL);
	spy_free = 0;

	assert_ptr_equal(lst, first);
	assert_int_equal(del_count, 0);
	assert_int_equal(free_count, 0);

	free(node);
	free(lst);
}

static void test_null_list(void **state)
{
	(void)state;
	reset_spies();

	spy_free = 1;
	ft_lstclear(NULL, del_wrapped);
	spy_free = 0;

	assert_int_equal(del_count, 0);
	assert_int_equal(free_count, 0);
}

static void test_large(void **state)
{
	t_list	*lst  = ft_lstnew(NULL);
	t_list	*node = lst;
	int		i;

	(void)state;
	i = 1;
	while (i < LIST_SIZE)
	{
		node->next = ft_lstnew(NULL);
		node = node->next;
		i++;
	}

	reset_spies();

	spy_free = 1;
	ft_lstclear(&lst, del_wrapped);
	spy_free = 0;

	assert_null(lst);
	assert_int_equal(del_count, LIST_SIZE);
	assert_int_equal(free_count, LIST_SIZE);
}

int main(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_empty),
		cmocka_unit_test(test_one),
		cmocka_unit_test(test_three),
		cmocka_unit_test(test_null_del),
		cmocka_unit_test(test_null_list),
		cmocka_unit_test(test_large),
	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}
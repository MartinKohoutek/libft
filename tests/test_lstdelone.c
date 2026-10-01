#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include <stdlib.h>
#include "libft.h"

static int spy_free;
static void *deleted_content;
static void *freed_ptr;

void __real_free(void *ptr);
void __wrap_free(void *ptr)
{
	if (spy_free)
		freed_ptr = ptr;
	__real_free(ptr);
}

static void del_wrapped(void *content)
{
	deleted_content = content;
}

static void test_basic(void **state)
{
	char	*content = "Hello";
	t_list	*lst	 = ft_lstnew(content);

	(void)state;
	deleted_content = NULL;
	freed_ptr = NULL;

	spy_free = 1;
	ft_lstdelone(lst, del_wrapped);
	spy_free = 0;

	assert_ptr_equal(deleted_content, content);
	assert_ptr_equal(freed_ptr, lst);
}

static void test_null_content(void **state)
{
	t_list	*lst = ft_lstnew(NULL);
	
	(void)state;
	deleted_content = NULL;
	freed_ptr = NULL;
	
	spy_free = 1;
	ft_lstdelone(lst, del_wrapped);
	spy_free = 0;

	assert_null(deleted_content);
	assert_ptr_equal(freed_ptr, lst);
}

// delone nesmaze dalsi node v seznamu
static void test_next(void **state)
{
	t_list	*lst  = ft_lstnew("A");
	t_list	*next = ft_lstnew("B");
	lst->next = next;

	(void)state;
	deleted_content = NULL;
	freed_ptr = NULL;
	
	spy_free = 1;
	ft_lstdelone(lst, del_wrapped);
	spy_free = 0;

	assert_ptr_equal(deleted_content, "A");
	assert_ptr_equal(freed_ptr, lst);
	assert_ptr_equal(next->content, "B");
	assert_null(next->next);

	free(next);
}

static void test_null_list(void **state)
{
	(void)state;

	deleted_content = NULL;
	freed_ptr = NULL;
	
	spy_free = 1;
	ft_lstdelone(NULL, del_wrapped);
	spy_free = 0;

	assert_null(deleted_content);
	assert_null(freed_ptr);
}

static void test_null_del(void **state)
{
	t_list	*lst = ft_lstnew("Hello");

	(void)state;
	deleted_content = NULL;
	freed_ptr = NULL;

	spy_free = 1;
	ft_lstdelone(lst, NULL);
	spy_free = 0;

	assert_null(deleted_content);
	assert_null(freed_ptr);

	free(lst);
}

int main(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_basic),
		cmocka_unit_test(test_null_content),
		cmocka_unit_test(test_next),
		cmocka_unit_test(test_null_list),
		cmocka_unit_test(test_null_del),
	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}
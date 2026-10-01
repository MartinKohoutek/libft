#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include <stdlib.h>
#include "libft.h"

static int fail_malloc;

void	*__real_malloc(size_t size);
void	*__wrap_malloc(size_t size)
{
	if (fail_malloc)
		return (NULL);
	return (__real_malloc(size));
}

static void test_basic(void **state)
{
	char	*content = "Hello, 42 Prague";
	t_list	*node = ft_lstnew(content);

	(void)state;
	assert_non_null(node);
	assert_ptr_equal(node->content, content);
	assert_null(node->next);

	free(node);
}

static void test_null_content(void **state)
{
	t_list	*node = ft_lstnew(NULL);

	(void)state;
	assert_non_null(node);
	assert_null(node->content);
	assert_null(node->next);

	free (node);
}

static void test_int_content(void **state)
{
	int		value = 42;
	t_list	*node = ft_lstnew(&value);
	
	(void)state;
	assert_non_null(node);
	assert_ptr_equal(node->content, &value);
	assert_int_equal(*(int *)node->content, 42);
	assert_null(node->next);

	free(node);
}

static void test_malloc_fail(void **state)
{
	t_list	*node;

	(void)state;
	fail_malloc = 1;
	node = ft_lstnew("Hello");
	fail_malloc = 0;
	assert_null(node);
}

int main(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_basic),
		cmocka_unit_test(test_null_content),
		cmocka_unit_test(test_int_content),
		cmocka_unit_test(test_malloc_fail),
	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}
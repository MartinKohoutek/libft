#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdlib.h>
#include "libft.h"

static int malloc_count = 0;
static int malloc_fail_at = -1;

void *__real_malloc(size_t size);
void *__wrap_malloc(size_t size)
{
	if (malloc_count++ == malloc_fail_at)
		return (NULL);
	return (__real_malloc(size));
}

static void	assert_strjoin(const char *s1, const char *s2, const char *expected)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	assert_non_null(res);
	assert_string_equal(res, expected);
	free(res);
}

static void	test_basic(void **state)
{
	(void)state;
	assert_strjoin("Hello, ", "42!", "Hello, 42!");
}

static void	test_empty_first(void **state)
{
	(void)state;
	assert_strjoin("", "42!", "42!");
}

static void	test_empty_second(void **state)
{
	(void)state;
	assert_strjoin("Hello", "", "Hello");
}

static void	test_both_empty(void **state)
{
	(void)state;
	assert_strjoin("", "", "");
}

static void	test_one_char(void **state)
{
	(void)state;
	assert_strjoin("A", "B", "AB");
}

static void	test_special_chars(void **state)
{
	(void)state;
	assert_strjoin("42\t", "\nPrague!", "42\t\nPrague!");
}

static void	test_malloc_failure(void **state)
{
	char	*res;

	(void)state;
	malloc_count = 0;
	malloc_fail_at = 0;
	res = ft_strjoin("Hello", "42");
	assert_null(res);
	malloc_fail_at = -1;
}

int main(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_basic),
		cmocka_unit_test(test_empty_first),
		cmocka_unit_test(test_empty_second),
		cmocka_unit_test(test_both_empty),
		cmocka_unit_test(test_one_char),
		cmocka_unit_test(test_special_chars),
		cmocka_unit_test(test_malloc_failure),
	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}
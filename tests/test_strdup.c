#include "libft.h"
#include <cmocka.h>
#include <string.h>
#include <stdlib.h>

static int malloc_count = 0;
static int malloc_fail_at = -1;

static void assert_strdup(const char *s, const char *expected)
{
	char *res;

	res = ft_strdup(s);
	assert_non_null(res);
	assert_string_equal(res, expected);
	assert_ptr_not_equal(res, s);
	free(res);
}

static void test_basic(void **state)
{
	(void)state;
	assert_strdup("Hello, 42!", "Hello, 42!");
}

static void test_empty(void **state)
{
	(void)state;
	assert_strdup("", "");
}

static void test_one(void **state)
{
	(void)state;
	assert_strdup("A", "A");
}

static void test_special_chars(void **state)
{
	(void)state;
	assert_strdup("Hello 42!\n\t", "Hello 42!\n\t");
}

void *__real_malloc(size_t size);
void *__wrap_malloc(size_t size)
{
	if (malloc_count++ == malloc_fail_at)
		return (NULL);
	return (__real_malloc(size));
}

static void test_malloc_failure(void **state)
{
	char *res;

	(void)state;
	malloc_count = 0;
	malloc_fail_at = 0;
	res = ft_strdup("abcdef");
	assert_null(res);
	malloc_fail_at = -1;
}

int main(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_basic),
		cmocka_unit_test(test_empty),
		cmocka_unit_test(test_one),
		cmocka_unit_test(test_special_chars),
		cmocka_unit_test(test_malloc_failure),
	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}

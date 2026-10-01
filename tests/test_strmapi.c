#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include <stdlib.h>
#include "libft.h"

static int malloc_fail_at = -1;
static int malloc_count = 0;

static char	even(unsigned int i, char c)
{
	if (i % 2 == 0)
		return ('E');
	return (c);
}

static char	caesar(unsigned int i, char c)
{
	return (c + i);
}

static char	index_to_char(unsigned int i, char c)
{
	(void)c;
	return ('0' + i);
}

static void	assert_strmapi(const char *s, char (*f)(unsigned int, char), 
	char *expected)
{
	char	*res;

	res = ft_strmapi(s, f);
	assert_non_null(res);
	assert_string_equal(res, expected);
	free(res);
}

void	*__real_malloc(size_t size);
void	*__wrap_malloc(size_t size)
{
	if (malloc_count++ == malloc_fail_at)
		return (NULL);
	return (__real_malloc(size));
}

static void	test_even(void **state)
{
	(void)state;
	assert_strmapi("abcdef", even, "EbEdEf");
}

// Dulezite pro i = 0;
static void	test_one(void **state)
{
	(void)state;
	assert_strmapi("a", even, "E");
}

static void	test_empty(void **state)
{
	(void)state;
	assert_strmapi("", even, "");
}

static void	test_null(void **state)
{
	char	*res;

	(void)state;
	res = ft_strmapi(NULL, even);
	assert_null(res);
}

static void	test_index(void **state)
{
	(void)state;
	assert_strmapi("abcdef", index_to_char, "012345");
}

static void	test_malloc_failure(void **state)
{
	char	*res;

	(void)state;
	malloc_count = 0;
	malloc_fail_at = 0;
	res = ft_strmapi("abcdef", even);
	assert_null(res);
	malloc_fail_at = -1;
}

static void	test_caesar(void **state)
{
	(void)state;
	assert_strmapi("abcdef", caesar, "acegik");
}

int main(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_even),
		cmocka_unit_test(test_one),
		cmocka_unit_test(test_empty),
		cmocka_unit_test(test_null),
		cmocka_unit_test(test_index),
		cmocka_unit_test(test_malloc_failure),
		cmocka_unit_test(test_caesar),
	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}
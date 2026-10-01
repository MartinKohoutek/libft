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

static void test_basic(void **state)
{
	int		*p;
	size_t	i;

	(void)state;
	p = ft_calloc(5, sizeof(int));
	assert_non_null(p);
	i = 0;
	while (i < 5)
	{
		assert_int_equal(p[i], 0);
		i++;
	}
	free(p);
}

static void test_zero_nmemb(void **state)
{
	void	*p;

	(void)state;
	p = ft_calloc(0, 10);
	assert_non_null(p);
	free(p);
}

static void test_zero_size(void **state)
{
	void	*p;

	(void)state;
	p = ft_calloc(10, 0);
	assert_non_null(p);
	free(p);
}

static void test_one(void **state)
{
	char	*p;

	(void)state;
	p = ft_calloc(1, 1);
	assert_non_null(p);
	assert_int_equal(*p, 0);
	free(p);
}

static void test_large(void **state)
{
	char	*p;
	size_t	i;

	(void)state;
	p = ft_calloc(100, sizeof(char));
	assert_non_null(p);
	i = 0;
	while (i < 100)
	{
		assert_int_equal(p[i], 0);
		i++;
	}
	free(p);
}

static void test_malloc_failure(void **state)
{
	void	*p;

	(void)state;
	malloc_count = 0;
	malloc_fail_at = 0;
	p = ft_calloc(10, sizeof(int));
	assert_null(p);
	malloc_fail_at = -1;
}

static void test_overflow(void **state)
{
	void	*p;

	(void)state;
	p = ft_calloc((size_t)-1, 2);
	assert_null(p);
}

int main(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_basic),
		cmocka_unit_test(test_zero_size),
		cmocka_unit_test(test_zero_nmemb),
		cmocka_unit_test(test_one),
		cmocka_unit_test(test_large),
		cmocka_unit_test(test_malloc_failure),
		cmocka_unit_test(test_overflow),
	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}
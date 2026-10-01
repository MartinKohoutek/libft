#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

// Normalni
// 		basic - substring uprostred ✅
//		start = 0 - zacatek retezce ✅
//		cely string

// Hranice
//		len presahuje konec - vrati zbytek stringu ✅
//		start = strlen(s) - prazdny vysledek ✅
//		start > strlen(s) - prazdny vysledek ✅
//		len = 0 - prazdny vysledek ✅
// 		cely string - start = 0, dostatecne velke len ✅

// Edge cases
//		prazdny s ✅

// Return Value
//		return value - obsah vysledku

// Alokace
//		vysledek je samostatne alokovany

static void test_basic(void **state)
{
	char		*res;
	const char	*s = "Hello, 42 Prague";

	(void)state;
	res = ft_substr(s, 7, 2);
	assert_string_equal(res, "42");
	free(res);
}

static void test_start_zero(void **state)
{
	char		*res;
	const char 	*s = "Hello, 42 Prague";
	
	(void)state;
	res = ft_substr(s, 0, 5);
	assert_string_equal(res, "Hello");
	free(res);
}

static void test_len_exceeds_end(void **state)
{
	char		*res;
	const char	*s = "Hello, 42 Prague";

	(void)state;
	res = ft_substr(s, 7, 100);
	assert_string_equal(res, "42 Prague");
	free(res);
}

static void test_start_at_end(void **state)
{
	char		*res;
	const char	*s = "Hello, 42 Prague";

	(void)state;
	res = ft_substr(s, ft_strlen(s), 5);
	assert_string_equal(res, "");
	free(res);
}

static void test_start_after_end(void **state)
{
	char		*res;
	const char	*s = "Hello, 42 Prague";

	(void)state;
	res = ft_substr(s, ft_strlen(s) + 5, 5);
	assert_string_equal(res, "");
	free(res);
}

static void test_len_zero(void **state)
{
	char		*res;
	const char	*s = "Hello, 42 Prague";

	(void)state;
	res = ft_substr(s, 7, 0);
	assert_string_equal(res, "");
	free(res);
}

static void test_whole_string(void **state)
{
	char		*res;
	const char	*s = "Hello, 42 Prague";

	(void)state;
	res = ft_substr(s, 0, 100);
	assert_string_equal(res, s);
	free(res);
}

static void test_empty_string(void **state)
{
	char		*res;
	const char	*s = "";

	(void)state;
	res = ft_substr(s, 0, 5);
	assert_string_equal(res, "");
	free(res);
}

static void test_allocation(void **state)
{
	char		*res;
	const char	*s = "Hello, 42 Prague";

	(void)state;
	res = ft_substr(s, 7, 2);
	assert_non_null(res);
	assert_ptr_not_equal(res, s);
	assert_string_equal(res, "42");
	free(res);
}

// neni soucast kontraktu !!!
static void test_null_string(void **state)
{
	char		*res;

	(void)state;
	res = ft_substr(NULL, 0, 5);
	assert_null(res);
}

// Mockovani - nastavime malloc na fail (NULL)
static int	fail_malloc;
void	*__real_malloc(size_t size);
void	*__wrap_malloc(size_t size)
{
	if (fail_malloc)
		return (NULL);
	return (__real_malloc(size));
}

static void test_malloc_failure(void **state)
{
	char		*res;

	(void)state;
	fail_malloc = 1;
	res = ft_substr("Hello, 42 Prague", 7, 2);
	fail_malloc = 0;
	assert_null(res);
}

int main(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_basic),
		cmocka_unit_test(test_start_zero),
		cmocka_unit_test(test_len_exceeds_end),
		cmocka_unit_test(test_start_at_end),
		cmocka_unit_test(test_start_after_end),
		cmocka_unit_test(test_len_zero),
		cmocka_unit_test(test_whole_string),
		cmocka_unit_test(test_empty_string),
		cmocka_unit_test(test_allocation),
		cmocka_unit_test(test_null_string),
		cmocka_unit_test(test_malloc_failure),
	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}
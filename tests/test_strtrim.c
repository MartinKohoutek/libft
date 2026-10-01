#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

// Normalni
//		basic - trim z obou stran ✅
//		trim pouze zleva ✅
//		trim pouze zprava ✅
//		nic se netrimuje ✅

// Hranice
//		cely string je tvořen setem ✅
//		jeden znak ✅

// Edge cases
//		prazdny s1 ✅
//		prazdny set ✅
//		s1 obsahuje pouze trimovaci znaky ✅

// Alokace
//		vysledek je samostatne alokovany ✅
//		malloc failure ✅

// Mockovani - nastavime malloc na fail (NULL)
static int	fail_malloc;
void	*__real_malloc(size_t size);
void	*__wrap_malloc(size_t size)
{
	if (fail_malloc)
		return (NULL);
	return (__real_malloc(size));
}

static void test_basic(void **state)
{
	char		*res;
	const char	*s1 = "xxxHello, 42 Praguexxx";
	const char	*set = "x";

	(void)state;
	res = ft_strtrim(s1, set);
	assert_string_equal(res, "Hello, 42 Prague");
	free(res);
}

static void test_trim_left(void **state)
{
	char		*res;
	const char	*s1 = "xxxHello, 42 Prague";
	const char	*set = "x";

	(void)state;
	res = ft_strtrim(s1, set);
	assert_string_equal(res, "Hello, 42 Prague");
	free(res);
}

static void test_trim_right(void **state)
{
	char		*res;
	const char	*s1 = "Hello, 42 Praguexxx";
	const char	*set = "x";

	(void)state;
	res = ft_strtrim(s1, set);
	assert_string_equal(res, "Hello, 42 Prague");
	free(res);
}

static void test_no_trim(void **state)
{
	char		*res;
	const char	*s1 = "Hello, 42 Prague";
	const char	*set = "x";

	(void)state;
	res = ft_strtrim(s1, set);
	assert_string_equal(res, s1);
	free(res);
}

static void test_multiple_set_chars(void **state)
{
	char		*res;
	const char	*s1 = "xx..Hello, 42 Prague..xx";
	const char	*set = "x.";

	(void)state;
	res = ft_strtrim(s1, set);
	assert_string_equal(res, "Hello, 42 Prague");
	free(res);
}

static void test_all_trim_chars(void **state)
{
	char		*res;
	const char	*s1 = "xx..xx";
	const char	*set = "x.";

	(void)state;
	res = ft_strtrim(s1, set);
	assert_string_equal(res, "");
	free(res);
}

static void test_single_char(void **state)
{
	char		*res;
	const char	*s1 = "xxx";
	const char	*set = "x";

	(void)state;
	res = ft_strtrim(s1, set);
	assert_string_equal(res, "");
	free(res);
}

static void test_empty_string(void **state)
{
	char		*res;
	const char	*s1 = "";
	const char	*set = "x.";

	(void)state;
	res = ft_strtrim(s1, set);
	assert_string_equal(res, "");
	free(res);
}

static void test_empty_set(void **state)
{
	char		*res;
	const char	*s1 = "Hello, 42 Prague";
	const char	*set = "";

	(void)state;
	res = ft_strtrim(s1, set);
	assert_string_equal(res, s1);
	free(res);
}

static void test_allocation(void **state)
{
	char		*res;
	const char	*s1 = "xxxHello, 42 Praguexxx";
	const char	*set = "x";

	(void)state;
	res = ft_strtrim(s1, set);
	assert_non_null(res);
	assert_ptr_not_equal(res, s1);
	assert_string_equal(res, "Hello, 42 Prague");
	free(res);
}

static void test_malloc_failure(void **state)
{
	char		*res;

	(void)state;
	fail_malloc = 1;
	res = ft_strtrim("xxxHello, 42 Praguexxx", "x");
	fail_malloc = 0;
	assert_null(res);
}

int main(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_basic),
		cmocka_unit_test(test_trim_left),
		cmocka_unit_test(test_trim_right),
		cmocka_unit_test(test_no_trim),
		cmocka_unit_test(test_multiple_set_chars),
		cmocka_unit_test(test_all_trim_chars),
		cmocka_unit_test(test_single_char),
		cmocka_unit_test(test_empty_string),
		cmocka_unit_test(test_empty_set),
		cmocka_unit_test(test_allocation),
		cmocka_unit_test(test_malloc_failure),
	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}
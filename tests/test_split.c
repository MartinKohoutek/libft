#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

#define MAX_RES 10

static int		free_track;
static int		free_count;
static int		malloc_call;
static int		malloc_fail_at;
static int		malloc_track;
static int		malloc_count;

static int	setup(void **state)
{
	(void)state;
	free_track = 0;
	free_count = 0;
	malloc_track = 0;
	malloc_count = 0;
	malloc_call = 0;
	malloc_fail_at = 0;
	return (0);
}

static void assert_split(char **actual, const char **expected)
{
	size_t	i	= 0;

	while (expected[i])
	{
		assert_non_null(actual[i]);
		assert_string_equal(actual[i], expected[i]);
		i++;
	}
	assert_null(actual[i]);
}

static void free_split(char **split)
{
	size_t	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static void test_empty_string(void **state)
{
	char		**res;
	const char	*ref[] = {NULL};

	(void)state;

	res = ft_split("", ' ');

	assert_non_null(res);
	assert_split(res, ref);

	free_split(res);
}

static void	test_one_word(void **state)
{
	char		**res;
	const char	*expected[] = {"abc", NULL};

	(void)state;

	res = ft_split("abc", ' ');

	assert_non_null(res);
	assert_split(res, expected);

	free_split(res);
}

static void test_two_words(void **state)
{
	char		**res;
	const char	*ref[] = {"abc", "def", NULL};

	(void)state;
	res = ft_split("abc def", ' ');
	
	assert_non_null(res);
	assert_split(res, ref);

	free_split(res);
}

static void	test_three_words(void **state)
{
	char		**res;
	const char	*expected[] = {"abc", "def", "ghi", NULL};

	(void)state;

	res = ft_split("abc def ghi", ' ');

	assert_non_null(res);
	assert_split(res, expected);

	free_split(res);
}

static void	test_leading_delimiter(void **state)
{
	char		**res;
	const char	*expected[] = {"abc", NULL};

	(void)state;
	res = ft_split(" abc", ' ');
	assert_non_null(res);
	assert_split(res, expected);
	free_split(res);
}

static void	test_trailing_delimiter(void **state)
{
	char		**res;
	const char	*expected[] = {"abc", NULL};

	(void)state;
	res = ft_split("abc ", ' ');
	assert_non_null(res);
	assert_split(res, expected);
	free_split(res);
}

static void	test_delimiters_around_word(void **state)
{
	char		**res;
	const char	*expected[] = {"abc", NULL};

	(void)state;
	res = ft_split(" abc ", ' ');
	assert_non_null(res);
	assert_split(res, expected);
	free_split(res);
}

static void	test_multiple_delimiters(void **state)
{
	char		**res;
	const char	*expected[] = {"abc", "def", NULL};

	(void)state;
	res = ft_split("abc   def", ' ');
	assert_non_null(res);
	assert_split(res, expected);
	free_split(res);
}

static void	test_only_delimiters(void **state)
{
	char		**res;
	const char	*expected[] = {NULL};

	(void)state;
	res = ft_split("     ", ' ');
	assert_non_null(res);
	assert_split(res, expected);
	free_split(res);
}

static void	test_comma_delimiter(void **state)
{
	char		**res;
	const char	*expected[] = {"abc", "def", "ghi", NULL};

	(void)state;
	res = ft_split("abc,def,ghi", ',');
	assert_non_null(res);
	assert_split(res, expected);
	free_split(res);
}

static void	test_tab_delimiter(void **state)
{
	char		**res;
	const char	*expected[] = {"abc", "def", NULL};

	(void)state;
	res = ft_split("abc\tdef", '\t');
	assert_non_null(res);
	assert_split(res, expected);
	free_split(res);
}

static void	test_one_character(void **state)
{
	char		**res;
	const char	*expected[] = {"a", NULL};

	(void)state;
	res = ft_split("a", ' ');
	assert_non_null(res);
	assert_split(res, expected);
	free_split(res);
}

static void	test_one_delimiter(void **state)
{
	char		**res;
	const char	*expected[] = {NULL};

	(void)state;
	res = ft_split(" ", ' ');
	assert_non_null(res);
	assert_split(res, expected);
	free_split(res);
}

void	__real_free(void *ptr);
void	__wrap_free(void *ptr)
{
	if (free_track)
		free_count++;
	__real_free(ptr);
}


void	*__real_malloc(size_t size);
void	*__wrap_malloc(size_t size)
{
	void	*ptr;

	malloc_call++;
	if (malloc_fail_at && malloc_call == malloc_fail_at)
		return (NULL);
	ptr = __real_malloc(size);
	if (malloc_track && ptr)
		malloc_count++;
	return (ptr);
}

static void	test_malloc_failure_first(void **state)
{
	char	**res;

	(void)state;
	malloc_fail_at = 1;

	res = ft_split("abc def", ' ');

	assert_null(res);
	assert_int_equal(malloc_call, 1);
}

static void	test_malloc_failure_second(void **state)
{
	char	**res;

	(void)state;
	malloc_fail_at = 2;
	malloc_track = 1;
	free_track = 1;

	res = ft_split("abc def", ' ');

	assert_null(res);
	assert_int_equal(malloc_call, 2);
	assert_int_equal(malloc_count, free_count);
}

static void	test_malloc_failure_third(void **state)
{
	char	**res;

	(void)state;
	malloc_fail_at = 3;
	malloc_track = 1;
	free_track = 1;

	res = ft_split("abc def ghi", ' ');

	assert_null(res);
	assert_int_equal(malloc_call, 3);
	assert_int_equal(malloc_count, free_count);
}

static void	test_null_delimiter(void **state)
{
	char		**res;
	const char	*expected[] = {"abc def", NULL};

	(void)state;
	res = ft_split("abc def", '\0');

	assert_split(res, expected);
	free_split(res);
}

static void	test_null_string(void **state)
{
	char	**res;

	(void)state;
	res = ft_split(NULL, ' ');

	assert_null(res);
}

int main(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_empty_string),
		cmocka_unit_test(test_one_word),
		cmocka_unit_test(test_two_words),
		cmocka_unit_test(test_three_words),
		cmocka_unit_test(test_leading_delimiter),
		cmocka_unit_test(test_trailing_delimiter),
		cmocka_unit_test(test_delimiters_around_word),
		cmocka_unit_test(test_multiple_delimiters),
		cmocka_unit_test(test_only_delimiters),
		cmocka_unit_test(test_comma_delimiter),
		cmocka_unit_test(test_tab_delimiter),
		cmocka_unit_test(test_one_character),
		cmocka_unit_test(test_one_delimiter),
		cmocka_unit_test_setup(test_malloc_failure_first, setup),
		cmocka_unit_test_setup(test_malloc_failure_second, setup),
		cmocka_unit_test_setup(test_malloc_failure_third, setup),
		cmocka_unit_test(test_null_delimiter),
		cmocka_unit_test(test_null_string),
	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}
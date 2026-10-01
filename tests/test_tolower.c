#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include "libft.h"

static void test_uppercase(void **state)
{
	(void)state;
	assert_int_equal(ft_tolower('A'), 'a');
	assert_int_equal(ft_tolower('N'), 'n');
	assert_int_equal(ft_tolower('Z'), 'z');
}

static void test_lowercase(void **state)
{
	(void)state;
	assert_int_equal(ft_tolower('a'), 'a');
	assert_int_equal(ft_tolower('m'), 'm');
	assert_int_equal(ft_tolower('z'), 'z');
}

static void test_other(void **state)
{
	(void)state;
	assert_int_equal(ft_tolower('0'), '0');
	assert_int_equal(ft_tolower('4'), '4');
	assert_int_equal(ft_tolower('9'), '9');
	assert_int_equal(ft_tolower(' '), ' ');
	assert_int_equal(ft_tolower('!'), '!');
	assert_int_equal(ft_tolower('~'), '~');
}

static void test_borders(void **state)
{
	(void)state;
	assert_int_equal(ft_tolower('@'), '@');
	assert_int_equal(ft_tolower('A'), 'a');
	assert_int_equal(ft_tolower('Z'), 'z');
	assert_int_equal(ft_tolower('['), '[');
}

static void test_eof(void **state)
{
	(void)state;
	assert_int_equal(ft_tolower(EOF), EOF);
}

int main(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_uppercase),
		cmocka_unit_test(test_lowercase),
		cmocka_unit_test(test_other),
		cmocka_unit_test(test_borders),
		cmocka_unit_test(test_eof),
	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}
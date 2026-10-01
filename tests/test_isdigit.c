#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include "libft.h"

static void test_digits(void **state)
{
	(void)state;
	assert_int_equal(ft_isdigit('0'), 1);
	assert_int_equal(ft_isdigit('4'), 1);
	assert_int_equal(ft_isdigit('9'), 1);
}

static void test_letters(void **state)
{
	(void)state;
	assert_int_equal(ft_isdigit('a'), 0);
	assert_int_equal(ft_isdigit('A'), 0);
	assert_int_equal(ft_isdigit('z'), 0);
	assert_int_equal(ft_isdigit('Z'), 0);
}

static void test_borders(void **state)
{
	(void)state;
	assert_int_equal(ft_isdigit('/'), 0);
	assert_int_equal(ft_isdigit(':'), 0);
}

static void test_other(void **state)
{
	(void)state;
	assert_int_equal(ft_isdigit(' '), 0);
	assert_int_equal(ft_isdigit('#'), 0);
	assert_int_equal(ft_isdigit('@'), 0);
}

static void test_eof(void **state)
{
	(void)state;
	assert_int_equal(ft_isdigit(EOF), 0);
}

int main(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_digits),
		cmocka_unit_test(test_letters),
		cmocka_unit_test(test_borders),
		cmocka_unit_test(test_other),
		cmocka_unit_test(test_eof),
	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}
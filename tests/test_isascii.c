#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include "libft.h"

static void test_letters(void **state)
{
	(void)state;
	assert_int_equal(ft_isascii('A'), 1);
	assert_int_equal(ft_isascii('m'), 1);
	assert_int_equal(ft_isascii('z'), 1);
}

static void test_digits(void **state)
{
	(void)state;
	assert_int_equal(ft_isascii('0'), 1);
	assert_int_equal(ft_isascii('4'), 1);
	assert_int_equal(ft_isascii('9'), 1);
}

static void test_other(void **state)
{
	(void)state;
	assert_int_equal(ft_isascii(' '), 1);
	assert_int_equal(ft_isascii('!'), 1);
	assert_int_equal(ft_isascii('~'), 1);
}

static void test_borders(void **state)
{
	(void)state;
	assert_int_equal(ft_isascii('\0'), 1);
	assert_int_equal(ft_isascii(127), 1);
	assert_int_equal(ft_isascii(128), 0);
}

static void test_eof(void **state)
{
	(void)state;
	assert_int_equal(ft_isascii(EOF), 0);
}

int main(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_letters),
		cmocka_unit_test(test_digits),
		cmocka_unit_test(test_other),
		cmocka_unit_test(test_borders),
		cmocka_unit_test(test_eof),
	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include "libft.h"

static void test_letters(void **state)
{
	(void)state;
	assert_int_equal(ft_isalnum('A'), 1);
	assert_int_equal(ft_isalnum('p'), 1);
	assert_int_equal(ft_isalnum('z'), 1);
}

static void test_digits(void **state)
{
	(void)state;
	assert_int_equal(ft_isalnum('0'), 1);
	assert_int_equal(ft_isalnum('4'), 1);
	assert_int_equal(ft_isalnum('9'), 1);
}

static void test_other(void **state)
{
	(void)state;
	assert_int_equal(ft_isalnum(' '), 0);
	assert_int_equal(ft_isalnum('!'), 0);
	assert_int_equal(ft_isalnum('_'), 0);
}

static void test_borders(void **state)
{
	(void)state;
	assert_int_equal(ft_isalnum('@'), 0);
	assert_int_equal(ft_isalnum('['), 0);
	assert_int_equal(ft_isalnum('`'), 0);
	assert_int_equal(ft_isalnum('{'), 0);
	assert_int_equal(ft_isalnum('/'), 0);
	assert_int_equal(ft_isalnum(':'), 0);
}

static void test_eof(void **state)
{
	(void)state;
	assert_int_equal(ft_isalnum(EOF), 0);
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
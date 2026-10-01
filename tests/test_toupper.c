#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include "libft.h"

static void test_lowercase(void **state)
{
	(void)state;
	assert_int_equal(ft_toupper('a'), 'A');
	assert_int_equal(ft_toupper('m'), 'M');
	assert_int_equal(ft_toupper('z'), 'Z');
}

static void test_uppercase(void **state)
{
	(void)state;
	assert_int_equal(ft_toupper('A'), 'A');
	assert_int_equal(ft_toupper('N'), 'N');
	assert_int_equal(ft_toupper('Z'), 'Z');
}

static void test_other(void **state)
{
	(void)state;
	assert_int_equal(ft_toupper('0'), '0');
	assert_int_equal(ft_toupper('4'), '4');
	assert_int_equal(ft_toupper('9'), '9');
	assert_int_equal(ft_toupper(' '), ' ');
	assert_int_equal(ft_toupper('!'), '!');
	assert_int_equal(ft_toupper('~'), '~');
}

static void test_borders(void **state)
{
	(void)state;
	assert_int_equal(ft_toupper('`'), '`');
	assert_int_equal(ft_toupper('a'), 'A');
	assert_int_equal(ft_toupper('z'), 'Z');
	assert_int_equal(ft_toupper('{'), '{');
}

static void test_eof(void **state)
{
	(void)state;
	assert_int_equal(ft_toupper(EOF), EOF);
}

int main(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_lowercase),
		cmocka_unit_test(test_uppercase),
		cmocka_unit_test(test_other),
		cmocka_unit_test(test_borders),
		cmocka_unit_test(test_eof),
	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}
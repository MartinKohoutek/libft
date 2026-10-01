#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include "libft.h"

static void test_uppercase(void **state)
{
	(void)state;
	assert_int_equal(ft_isalpha('A'), 1);
	assert_int_equal(ft_isalpha('P'), 1);
	assert_int_equal(ft_isalpha('Z'), 1);
}

static void test_lowercase(void **state)
{
	(void)state;
	assert_int_equal(ft_isalpha('a'), 1);
	assert_int_equal(ft_isalpha('p'), 1);
	assert_int_equal(ft_isalpha('z'), 1);
}

static void test_digits(void **state)
{
	(void)state;
	assert_int_equal(ft_isalpha('0'), 0);
	assert_int_equal(ft_isalpha('4'), 0);
	assert_int_equal(ft_isalpha('9'), 0);
}

static void test_other(void **state)
{
	(void)state;
	assert_int_equal(ft_isalpha(' '), 0);
	assert_int_equal(ft_isalpha('!'), 0);
	assert_int_equal(ft_isalpha('#'), 0);
}

static void test_borders(void **state)
{
	(void)state;
	assert_int_equal(ft_isalpha('@'), 0);
	assert_int_equal(ft_isalpha('['), 0);
	assert_int_equal(ft_isalpha('`'), 0);
	assert_int_equal(ft_isalpha('{'), 0);
}

static void test_eof(void **state)
{
	(void)state;
	assert_int_equal(ft_isalpha(EOF), 0);
}

int main(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_uppercase),
		cmocka_unit_test(test_lowercase),
		cmocka_unit_test(test_digits),
		cmocka_unit_test(test_other),
		cmocka_unit_test(test_borders),
		cmocka_unit_test(test_eof),
	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}
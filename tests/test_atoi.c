#include "libft.h"
#include <cmocka.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

static void	assert_atoi(const char *s)
{
	assert_int_equal(ft_atoi(s), atoi(s));
}

static void	test_positive(void **state)
{
	(void)state;
	assert_atoi("42");
}

static void	test_negative(void **state)
{
	(void)state;
	assert_atoi("-42");
}

static void	test_zero(void **state)
{
	(void)state;
	assert_atoi("0");
}

static void	test_leading_spaces(void **state)
{
	(void)state;
	assert_atoi("   42");
}

static void	test_leading_plus(void **state)
{
	(void)state;
	assert_atoi("+42");
}

static void	test_leading_minus(void **state)
{
	(void)state;
	assert_atoi("-42");
}

static void	test_spaces_and_sign(void **state)
{
	(void)state;
	assert_atoi(" \t\n\v\f\r -42");
}

static void	test_trailing_chars(void **state)
{
	(void)state;
	assert_atoi("42abc");
}

static void	test_only_chars(void **state)
{
	(void)state;
	assert_atoi("abc42");
}

static void	test_double_plus(void **state)
{
	(void)state;
	assert_atoi("++42");
}

static void	test_double_minus(void **state)
{
	(void)state;
	assert_atoi("--42");
}

static void	test_plus_minus(void **state)
{
	(void)state;
	assert_atoi("+-42");
}

static void	test_empty(void **state)
{
	(void)state;
	assert_atoi("");
}

static void	test_only_spaces(void **state)
{
	(void)state;
	assert_atoi("   ");
}

static void	test_only_plus(void **state)
{
	(void)state;
	assert_atoi("+");
}

static void	test_only_minus(void **state)
{
	(void)state;
	assert_atoi("-");
}

static void	test_spaces_plus(void **state)
{
	(void)state;
	assert_atoi("   +");
}

static void	test_spaces_minus(void **state)
{
	(void)state;
	assert_atoi("   -");
}

static void	test_leading_zeros(void **state)
{
	(void)state;
	assert_atoi("00042");
}

static void	test_negative_zero(void **state)
{
	(void)state;
	assert_atoi("-0");
}

static void	test_positive_zero(void **state)
{
	(void)state;
	assert_atoi("+0");
}

static void	test_space_between_sign_and_number(void **state)
{
	(void)state;
	assert_atoi("- 42");
}

static void	test_space_after_number(void **state)
{
	(void)state;
	assert_atoi("42 123");
}

static void	test_int_max(void **state)
{
	(void)state;
	assert_atoi("2147483647");
}

static void	test_int_min(void **state)
{
	(void)state;
	assert_atoi("-2147483648");
}

static void	test_long_number(void **state)
{
	(void)state;
	assert_atoi("00000000000000000000042");
}

static void	test_char_before_digit(void **state)
{
	(void)state;
	assert_atoi("/42");
}

static void	test_char_after_digit(void **state)
{
	(void)state;
	assert_atoi("42/");
}

int main(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_positive),
		cmocka_unit_test(test_negative),
		cmocka_unit_test(test_zero),
		cmocka_unit_test(test_leading_spaces),
		cmocka_unit_test(test_leading_plus),
		cmocka_unit_test(test_leading_minus),
		cmocka_unit_test(test_spaces_and_sign),
		cmocka_unit_test(test_trailing_chars),
		cmocka_unit_test(test_only_chars),
		cmocka_unit_test(test_double_plus),
		cmocka_unit_test(test_double_minus),
		cmocka_unit_test(test_plus_minus),
		cmocka_unit_test(test_empty),
		cmocka_unit_test(test_only_spaces),
		cmocka_unit_test(test_only_plus),
		cmocka_unit_test(test_only_minus),
		cmocka_unit_test(test_spaces_plus),
		cmocka_unit_test(test_spaces_minus),
		cmocka_unit_test(test_leading_zeros),
		cmocka_unit_test(test_negative_zero),
		cmocka_unit_test(test_positive_zero),
		cmocka_unit_test(test_space_between_sign_and_number),
		cmocka_unit_test(test_space_after_number),
		cmocka_unit_test(test_int_max),
		cmocka_unit_test(test_int_min),
		cmocka_unit_test(test_long_number),
		cmocka_unit_test(test_char_before_digit),
		cmocka_unit_test(test_char_after_digit),
	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}
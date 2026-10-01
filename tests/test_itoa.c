#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "libft.h"

static void assert_itoa(int n)
{
	char	*res;
	char	ref[32];

	snprintf(ref, sizeof(ref), "%d", n);
	res = ft_itoa(n);

	assert_non_null(res);
	assert_string_equal(res, ref);

	free(res);
}

static void test_zero(void **state)
{
	(void)state;
	assert_itoa(0);
}

static void test_positive(void **state)
{
	(void)state;
	assert_itoa(1);
	assert_itoa(9);
	assert_itoa(10);
	assert_itoa(42);
	assert_itoa(123);
	assert_itoa(1000);
	assert_itoa(1001);
	assert_itoa(123456789);
	assert_itoa(INT_MAX);
}

static void test_negative(void **state)
{
	(void)state;
	assert_itoa(-1);
	assert_itoa(-9);
	assert_itoa(-10);
	assert_itoa(-43);
	assert_itoa(-123);
	assert_itoa(-1000);
	assert_itoa(-1001);
	assert_itoa(-123456789);
	assert_itoa(INT_MIN);
}

int main(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_zero),
		cmocka_unit_test(test_positive),
		cmocka_unit_test(test_negative),
	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}
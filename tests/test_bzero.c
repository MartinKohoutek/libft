#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include <bsd/string.h>
#include "libft.h"

#define BUFFER_SIZE 20
#define TEST_STRING "Hello, 42 Prague"

static void test_bzero(size_t n)
{
	char	buffer[BUFFER_SIZE] = TEST_STRING;
	char	oracle[BUFFER_SIZE] = TEST_STRING;

	ft_bzero(buffer, n);
	bzero(oracle, n);
	assert_memory_equal(buffer, oracle, sizeof(buffer));
}

static void test_basic(void **state)
{
	(void)state;
	test_bzero(BUFFER_SIZE);
}

static void test_small_n(void **state)
{
	(void)state;
	test_bzero(BUFFER_SIZE / 2);
}

// buffer se nesmi zmenit
static void test_zero_n(void **state)
{
	(void)state;
	test_bzero(0);
}

static void test_one_n(void **state)
{
	(void)state;
	test_bzero(1);
}

// bzero musi vynulovat i bajty za '\0', ale posledni dva bajty nechat
static void test_after_null(void **state)
{
	(void)state;
	test_bzero(BUFFER_SIZE - 2);
}

int main(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_basic),
		cmocka_unit_test(test_small_n),
		cmocka_unit_test(test_zero_n),
		cmocka_unit_test(test_one_n),
		cmocka_unit_test(test_after_null),
	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include "libft.h"

static void test_strlen(const char *s)
{
	assert_int_equal(ft_strlen(s), strlen(s));
}


static void test_basic(void **state)
{
	(void)state;
	test_strlen("Hello, 42 Prague");
}

static void test_empty(void **state)
{
	(void)state;
	test_strlen("");
}

static void test_one_char(void **state)
{
	(void)state;
	test_strlen("A");
}

static void test_null(void **state)
{
	char	buffer[] = "ABC\0DEF";

	(void)state;
	test_strlen(buffer);
}

static void test_multiple_nulls(void **state)
{
	char	buffer[] = "ABC\0\0DEF";

	(void)state;
	test_strlen(buffer);
}

static void test_null_at_start(void **state)
{
	char	buffer[] = "\0ABCDEF";

	(void)state;
	test_strlen(buffer);
}

static void test_whitespace(void **state)
{
	char	buffer[] = "   \t\n";

	(void)state;
	test_strlen(buffer);
}

static void test_long(void **state)
{
	char	buffer[1001];
	
	memset(buffer, 'X', 1000);
	buffer[1000] = '\0';

	(void)state;
	test_strlen(buffer);
}

static void test_high_bytes(void **state)
{
	char	buffer[] = "\x80\x81\xFE\xFF";

	(void)state;
	test_strlen(buffer);
}


int main(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_basic),
		cmocka_unit_test(test_empty),
		cmocka_unit_test(test_one_char),
		cmocka_unit_test(test_null),
		cmocka_unit_test(test_multiple_nulls),
		cmocka_unit_test(test_null_at_start),
		cmocka_unit_test(test_whitespace),
		cmocka_unit_test(test_long),
		cmocka_unit_test(test_high_bytes),
	};
	
	return cmocka_run_group_tests(tests, NULL, NULL);
}
#include "libft.h"
#include <cmocka.h>
#include <string.h>

static void	assert_strchr(const char *s, int c)
{
	assert_ptr_equal(ft_strchr(s, c), strchr(s, c));
}

static void	test_first(void **state)
{
	const char	*s = "Hello, 42!";

	(void)state;
	assert_strchr(s, 'H');
}

static void	test_middle(void **state)
{
	const char	*s = "Hello, 42!";

	(void)state;
	assert_strchr(s, '4');
}

static void	test_last(void **state)
{
	const char	*s = "Hello, 42!";

	(void)state;
	assert_strchr(s, '!');
}

static void	test_not_found(void **state)
{
	const char	*s = "Hello, 42!";

	(void)state;
	assert_strchr(s, 'X');
}

static void	test_null(void **state)
{
	const char	*s = "Hello";

	(void)state;
	assert_strchr(s, '\0');
}

// 0x100 =>0x00 	-> najde terminator
static void	test_unsigned_char(void **state)
{
	const char	*s = "Hello";

	(void)state;
	assert_strchr(s, 0x100);
}

// -1 se prevede na 255 => nebude nalezen
static void	test_negative(void **state)
{
	const char	*s = "Hello";

	(void)state;
	assert_strchr(s, -1);
}

static void	test_first_occurrence(void **state)
{
	const char	*s = "ABCABC";

	(void)state;
	assert_strchr(s, 'B');
}

int main(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_first),
		cmocka_unit_test(test_middle),
		cmocka_unit_test(test_last),
		cmocka_unit_test(test_not_found),
		cmocka_unit_test(test_null),
		cmocka_unit_test(test_unsigned_char),
		cmocka_unit_test(test_negative),
		cmocka_unit_test(test_first_occurrence),
	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}
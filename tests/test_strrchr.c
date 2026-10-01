#include "libft.h"
#include <cmocka.h>
#include <string.h>

static void	assert_strrchr(const char *s, int c)
{
	assert_ptr_equal(ft_strrchr(s, c), strrchr(s, c));
}

static void	test_first(void **state)
{
	const char	*s = "Hello, 42!";

	(void)state;
	assert_strrchr(s, 'H');
}

static void	test_middle(void **state)
{
	const char	*s = "Hello, 42!";

	(void)state;
	assert_strrchr(s, '4');
}

static void	test_last(void **state)
{
	const char	*s = "Hello, 42!";

	(void)state;
	assert_strrchr(s, '!');
}

static void	test_not_found(void **state)
{
	const char	*s = "Hello, 42!";

	(void)state;
	assert_strrchr(s, 'X');
}

static void	test_last_occurrence(void **state)
{
	const char	*s = "ABCABC";

	(void)state;
	assert_strrchr(s, 'B');
}

// najde terminator
static void	test_null(void **state)
{
	const char	*s = "Hello";

	(void)state;
	assert_strrchr(s, '\0');
}

static void	test_unsigned_char(void **state)
{
	const char	*s = "Hello";

	(void)state;
	assert_strrchr(s, 0x100);
}

static void	test_negative_value(void **state)
{
	const char	*s = "Hello";

	(void)state;
	assert_strrchr(s, -1);
}

int main(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_first),
		cmocka_unit_test(test_middle),
		cmocka_unit_test(test_last),
		cmocka_unit_test(test_not_found),
		cmocka_unit_test(test_last_occurrence),
		cmocka_unit_test(test_null),
		cmocka_unit_test(test_unsigned_char),
		cmocka_unit_test(test_negative_value),
	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}
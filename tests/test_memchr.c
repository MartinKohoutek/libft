#include "libft.h"
#include <cmocka.h>
#include <string.h>

static void	assert_memchr(const void *s, int c, size_t n)
{
	assert_ptr_equal(ft_memchr(s, c, n), memchr(s, c, n));
}

static void	test_basic(void **state)
{
	char	s[] = "Hello, 42!";

	(void)state;
	assert_memchr(s, '4', sizeof(s));
}

static void	test_not_found(void **state)
{
	char	s[] = "Hello, 42!";

	(void)state;
	assert_memchr(s, 'X', sizeof(s));
}

// musi vratit NULL
static void	test_zero(void **state)
{
	char	s[] = "Hello, 42!";

	(void)state;
	assert_memchr(s, 'H', 0);
}

// musi najit null a vratit jeho pozici
static void	test_null(void **state)
{
	char	s[] = {'A', '\0', 'B', 'C'};

	(void)state;
	assert_memchr(s, '\0', sizeof(s));
}

// 0x100 se porovnava jako 00
static void	test_unsigned_char(void **state)
{
	unsigned char	s[] = {0x41, 0x00, 0x42};

	(void)state;
	assert_memchr(s, 0x100, sizeof(s));
}

static void	test_found_first(void **state)
{
	char	s[] = "ABCABC";

	(void)state;
	assert_memchr(s, 'B', sizeof(s));
}

// 'D' uz neni v povolenem rozsahu - 3 znaky
static void	test_out_of_range(void **state)
{
	char	s[] = "ABCDEF";

	(void)state;
	assert_memchr(s, 'D', 3);
}

int main(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_basic),
		cmocka_unit_test(test_not_found),
		cmocka_unit_test(test_zero),
		cmocka_unit_test(test_null),
		cmocka_unit_test(test_unsigned_char),
		cmocka_unit_test(test_found_first),
		cmocka_unit_test(test_out_of_range),
	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}
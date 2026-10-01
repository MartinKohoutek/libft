#include "libft.h"
#include <cmocka.h>
#include <string.h>

static void	assert_memcmp(const void *s1, const void *s2, size_t n)
{
	assert_int_equal(ft_memcmp(s1, s2, n), memcmp(s1, s2, n));
}

static void	test_equal(void **state)
{
	char	s1[] = "Hello, 42!";
	char	s2[] = "Hello, 42!";

	(void)state;
	assert_memcmp(s1, s2, sizeof(s1));
}

static void	test_first(void **state)
{
	char	s1[] = "Xello";
	char	s2[] = "Hello";

	(void)state;
	assert_memcmp(s1, s2, 5);
}

static void	test_middle(void **state)
{
	char	s1[] = "HeXlo";
	char	s2[] = "Hello";

	(void)state;
	assert_memcmp(s1, s2, 5);
}

static void	test_last(void **state)
{
	char	s1[] = "HellX";
	char	s2[] = "Hello";

	(void)state;
	assert_memcmp(s1, s2, 5);
}

// i kdyz se oba lisi, vysledek musi byt 0 (pro n = 0)
static void	test_zero(void **state)
{
	char	s1[] = "ABC";
	char	s2[] = "XYZ";

	(void)state;
	assert_memcmp(s1, s2, 0);
}

// \0 neni konec
static void	test_null(void **state)
{
	unsigned char	s1[] = {'A', 0, 'B'};
	unsigned char	s2[] = {'A', 0, 'C'};

	(void)state;
	assert_memcmp(s1, s2, sizeof(s1));
}

// prvni rozdil rozhoduje
static void	test_first_difference(void **state)
{
	unsigned char	s1[] = {1, 9, 9, 9};
	unsigned char	s2[] = {2, 0, 0, 0};

	(void)state;
	assert_memcmp(s1, s2, sizeof(s1));
}

// FF musi byt 255, ne -1 (rozdil char vs unsigned char)
static void	test_unsigned(void **state)
{
	unsigned char	s1[] = {0xFF};
	unsigned char	s2[] = {0x01};

	(void)state;
	assert_memcmp(s1, s2, 1);
}

// return = 0 (prvni 3 znaky jsou stejne)
// neporovna znaky za C
static void	test_prefix(void **state)
{
	char	s1[] = "ABCX";
	char	s2[] = "ABCY";

	(void)state;
	assert_memcmp(s1, s2, 3);
}

int main(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_equal),
		cmocka_unit_test(test_first),
		cmocka_unit_test(test_middle),
		cmocka_unit_test(test_last),
		cmocka_unit_test(test_zero),
		cmocka_unit_test(test_null),
		cmocka_unit_test(test_first_difference),
		cmocka_unit_test(test_unsigned),
		cmocka_unit_test(test_prefix),
	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}
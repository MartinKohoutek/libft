#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <bsd/string.h>
#include "libft.h"

// Basic
// 		shodné řetězce
// 		různé řetězce
// 		shoda na začátku
// 		rozdíl na začátku
// 		rozdíl uprostřed
// 		rozdíl na konci
// 		první rozdíl rozhoduje
//
// Delka
// 		n == 0
// 		n == 1
// 		n < strlen
// 		n == strlen
// 		n > strlen
//
// Prazdne retezce
// 		s1 == ""
// 		s2 == ""
// 		s1 == "", s2 == ""
//
// Znaky
// 		mezera
// 		speciální ASCII
// 		velká/malá písmena
// 		unsigned char hodnoty > 127
//
// Navratova hodnota
// 		0 při shodě
// 		záporná hodnota
// 		kladná hodnota
// 		přesný rozdíl unsigned char

static int	setup(void **state)
{
	*state = "Hello, 42 Prague";
	return (0);
}

static void	test_equal(void **state)
{
	const char	*s1 = *state;
	const char	*s2 = "Hello, 42 Prague";

	assert_int_equal(ft_strncmp(s1, s2, 16), 0);
}

static void	test_different(void **state)
{
	const char	*s1 = *state;
	const char	*s2 = "ABC56789";

	(void)state;
	assert_true(ft_strncmp(s1, s2, 16) > 0);
}

static void	test_same_start(void **state)
{
	const char	*s1 = *state;
	const char	*s2 = "Hello, Madrid 42";

	(void)state;
	assert_true(ft_strncmp(s1, s2, 16) < 0);
}

static void	test_different_start(void **state)
{
	const char	*s1 = *state;
	const char	*s2 = "Hallo, 42 Prague";

	(void)state;
	assert_true(ft_strncmp(s1, s2, 16) > 0);
}

static void	test_different_middle(void **state)
{
	const char	*s1 = *state;
	const char	*s2 = "Hello, 43 Prague";

	(void)state;
	assert_true(ft_strncmp(s1, s2, 16) < 0);
}

static void	test_different_end(void **state)
{
	const char	*s1 = *state;
	const char	*s2 = "Hello, 42 Madrid";

	(void)state;
	assert_true(ft_strncmp(s1, s2, 16) > 0);
}

// 2 vs 3, ne M vs P
static void	test_first_difference(void **state)
{
	const char	*s1 = *state;
	const char	*s2 = "Hello, 43 Madrid";

	(void)state;
	assert_true(ft_strncmp(s1, s2, 16) < 0);
}

static void	test_len_zero(void **state)
{
	const char	*s1 = *state;
	const char	*s2 = "ABC56789";

	(void)state;
	assert_int_equal(ft_strncmp(s1, s2, 0), 0);
}

static void	test_len_one(void **state)
{
	const char	*s1 = *state;
	const char	*s2 = "Hello, 43 Prague";

	(void)state;
	assert_int_equal(ft_strncmp(s1, s2, 1), 0);
}

// n < strlen (lisi se az za n znaku)
static void	test_short_len(void **state)
{
	const char	*s1 = *state;
	const char	*s2 = "Hello, 43 Prague";

	(void)state;
	assert_int_equal(ft_strncmp(s1, s2, 7), 0);
}

// n == strlen
static void	test_exact_len(void **state)
{
	const char	*s1 = *state;
	const char	*s2 = "Hello, 42 Prague";

	(void)state;
	assert_int_equal(ft_strncmp(s1, s2, 16), 0);
}

static void	test_long_len(void **state)
{
	const char	*s1 = *state;
	const char	*s2 = "Hello, 42 Prague";

	(void)state;
	assert_int_equal(ft_strncmp(s1, s2, 100), 0);
}

// return negative number (\0 - 'H')
static void	test_empty_s1(void **state)
{
	const char	*s1 = "";
	const char	*s2 = *state;

	(void)state;
	assert_true(ft_strncmp(s1, s2, 16) < 0);
}

// return positive number ('H' - '\0')
static void	test_empty_s2(void **state)
{
	const char	*s1 = *state;
	const char	*s2 = "";

	(void)state;
	assert_true(ft_strncmp(s1, s2, 16) > 0);
}

// return 0 (\0 - \0)
static void	test_empty_both(void **state)
{
	const char	*s1 = "";
	const char	*s2 = "";

	(void)state;
	assert_int_equal(ft_strncmp(s1, s2, 16), 0);
}

static void	test_space(void **state)
{
	const char	*s1 = "abc def";
	const char	*s2 = "abc  def";

	(void)state;
	assert_true(ft_strncmp(s1, s2, 16) > 0);
}

static void	test_special_chars(void **state)
{
	const char	*s1 = "abc!@#";
	const char	*s2 = "abc!$#";

	(void)state;
	assert_true(ft_strncmp(s1, s2, 16) > 0);
}

static void	test_case_sensitivity(void **state)
{
	const char	*s1 = "Hello";
	const char	*s2 = "hello";

	(void)state;
	assert_true(ft_strncmp(s1, s2, 16) < 0);
}

// Test unsigned char > 127
static void	test_unsigned_char(void **state)
{
	const char	*s1 = "\x80";
	const char	*s2 = "\x81";

	(void)state;
	assert_int_equal(ft_strncmp(s1, s2, 1), strncmp(s1, s2, 1));
}

static void	test_return_zero(void **state)
{
	const char	*s1 = "ABC";
	const char	*s2 = "ABC";

	(void)state;
	assert_true(ft_strncmp(s1, s2, 16) == 0);
}

static void	test_return_negative(void **state)
{
	const char	*s1 = "ABC";
	const char	*s2 = "ABD";

	(void)state;
	assert_true(ft_strncmp(s1, s2, 16) < 0);
}

static void	test_return_positive(void **state)
{
	const char	*s1 = "ABD";
	const char	*s2 = "ABC";

	(void)state;
	assert_true(ft_strncmp(s1, s2, 16) > 0);
}

// ISO C guarantees only the sign of the result,
// not its exact value.
// This exact-value behavior applies only to GNU libc.
static void	test_gnu_return_value(void **state)
{
	const char	*s1 = "\x80";
	const char	*s2 = "\x82";

	(void)state;
	assert_int_equal(ft_strncmp(s1, s2, 16), -2);
}

int	main(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_equal),
		cmocka_unit_test(test_different),
		cmocka_unit_test(test_same_start),
		cmocka_unit_test(test_different_start),
		cmocka_unit_test(test_different_middle),
		cmocka_unit_test(test_different_end),
		cmocka_unit_test(test_first_difference),
		cmocka_unit_test(test_len_zero),
		cmocka_unit_test(test_len_one),
		cmocka_unit_test(test_short_len),
		cmocka_unit_test(test_exact_len),
		cmocka_unit_test(test_long_len),
		cmocka_unit_test(test_empty_s1),
		cmocka_unit_test(test_empty_s2),
		cmocka_unit_test(test_empty_both),
		cmocka_unit_test(test_space),
		cmocka_unit_test(test_special_chars),
		cmocka_unit_test(test_case_sensitivity),
		cmocka_unit_test(test_unsigned_char),
		cmocka_unit_test(test_return_zero),
		cmocka_unit_test(test_return_negative),
		cmocka_unit_test(test_return_positive),
		cmocka_unit_test(test_gnu_return_value),
	};

	return (cmocka_run_group_tests(tests, setup, NULL));
}
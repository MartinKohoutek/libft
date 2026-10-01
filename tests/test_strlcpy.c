#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <bsd/string.h>
#include "libft.h"
#include <stdio.h>

// Basic
// 		cíl dostatečně velký ✅
// 		cíl menší než zdroj ✅
// 		stejný obsah ✅
//
// Velikost
// 		size == 0 ✅
// 		size == 1 ✅
// 		size < strlen(src) ✅
// 		size == strlen(src) ✅
// 		size > strlen(src) ✅
//
// Prázdné řetězce
// 		src == "" ✅
// 		size == 0, src = "" ✅
//
// Návratová hodnota
// 		vrací strlen(src) ✅

static int setup(void **state)
{
	*state = "Hello, 42 Prague";
	return (0);
}

static void	test_basic(void **state)
{
	const char	*s = *state;
	char		dest[32];
	char		ref[32];

	assert_int_equal(ft_strlcpy(dest, s, sizeof(dest)),
		strlcpy(ref, s, sizeof(ref)));
	assert_string_equal(dest, ref);
}

static void test_dest_small(void **state)
{
	const char *s = *state;
	char		dest[8];
	char		ref[8];

	assert_int_equal(ft_strlcpy(dest, s, sizeof(dest)), 
		strlcpy(ref, s, sizeof(ref)));
	assert_string_equal(dest, ref);
}

// size = 0: do dest se nesmi zapsat a fce ma vratit srclen
static void test_size_zero(void **state)
{
	const char *s = *state;
	char	dest[8] = "xxxxxxx";
	char	ref[8] = "xxxxxxx";

	assert_int_equal(ft_strlcpy(dest, s, 0), strlcpy(ref, s, 0));
	assert_memory_equal(dest, ref, sizeof(dest));
}

// size = 1: nezkopiruje zadny znak, jen \0
static void test_size_one(void **state)
{
	const char *s = *state;
	char	dest[1];
	char	ref[1];

	assert_int_equal(ft_strlcpy(dest, s, 1), strlcpy(ref, s, 1));
	assert_memory_equal(dest, ref, sizeof(dest));
}

// size < strlen: truncation, musi pridat \0
static void test_small_size(void **state)
{
	const char *s = *state;
	char	dest[6];
	char	ref[6];

	assert_int_equal(ft_strlcpy(dest, s, 6), strlcpy(ref, s, 6));
	assert_memory_equal(dest, ref, sizeof(dest));
	assert_int_equal(dest[5], '\0');
}

// size == strlen
// musi vratit "Hello, 42 Pragu\0" (posledni znak se nevejde !!!)
static void test_equal_size(void **state)
{
	const char *s = *state;
	char	dest[16];
	char	ref[16];

	assert_int_equal(ft_strlcpy(dest, s, 16), strlcpy(ref, s, 16));
	assert_memory_equal(dest, ref, 16);
	assert_int_equal(dest[15], '\0');
}

static void test_big_size(void **state)
{
	const char *s = *state;
	char	dest[32];
	char	ref[32];

	assert_int_equal(ft_strlcpy(dest, s, 17), strlcpy(ref, s, 17));
	assert_memory_equal(dest, ref, 17);
	assert_string_equal(dest, s);
}

static void test_empty_src(void **state)
{
	const char *s = "";
	char	dest[8];
	char	ref[8];

	(void)state;
	assert_int_equal(ft_strlcpy(dest, s, sizeof(dest)), 
		strlcpy(ref, s, sizeof(ref)));
	assert_memory_equal(dest, ref, 1);
	assert_int_equal(dest[0], '\0');
}

// size = 0, src = "": fce nesmi zmenit ani jeden bajt, a vraci 0
static void test_empty_src_zero_size(void **state)
{
	const char *s = "";
	char	dest[8] = "xxxxxxx";
	char	ref[8] = "xxxxxxx";

	(void)state;
	assert_int_equal(ft_strlcpy(dest, s, 0), strlcpy(ref, s, 0));
	assert_memory_equal(dest, ref, sizeof(dest));
}

static void test_return_value(void **state)
{
	const char *s = *state;
	char	dest[32];

	assert_int_equal(ft_strlcpy(dest, s, 0), 16);
	assert_int_equal(ft_strlcpy(dest, s, 1), 16);
	assert_int_equal(ft_strlcpy(dest, s, 8), 16);
	assert_int_equal(ft_strlcpy(dest, s, 16), 16);
	assert_int_equal(ft_strlcpy(dest, s, 17), 16);
	assert_int_equal(ft_strlcpy(dest, s, 32), 16);
}

int main(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_basic),
		cmocka_unit_test(test_dest_small),
		cmocka_unit_test(test_size_zero),
		cmocka_unit_test(test_size_one),
		cmocka_unit_test(test_small_size),
		cmocka_unit_test(test_equal_size),
		cmocka_unit_test(test_big_size),
		cmocka_unit_test(test_empty_src),
		cmocka_unit_test(test_empty_src_zero_size),
		cmocka_unit_test(test_return_value),
	};

	return cmocka_run_group_tests(tests, setup, NULL);
}
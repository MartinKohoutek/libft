#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <bsd/string.h>
#include "libft.h"

// Basic
// 		začátek ✅
// 		uprostřed ✅
// 		konec ✅
// 		nenalezeno ✅
// 		více výskytů → musí vrátit první ✅
// Delka
// 		len == 0 ✅
// 		len == 1 ✅
// 		len < strlen(little) ✅
// 		len == strlen(little) ✅
// 		len přesně na hranici nalezení ✅
// 		match přesahující len ✅
// Prazdne retezce
// 		little == "" ✅
// 		big == "" ✅
// 		big == "", little == "" ✅
// Velikosti
// 		little delší než big ✅
// 		little stejně dlouhý jako big ✅
// Znaky
//		mezery ✅
//		speciální ASCII znaky ✅
//		case sensitivity ✅
// Navratova hodnota
//		správný pointer do big ✅
//		NULL při nenalezení

static int setup(void **state)
{
	*state = "Hello, 42 Prague";
	return (0);
}

static void test_start(void **state)
{
	const char *b = *state;
	const char *l = "Hello";

	assert_ptr_equal(ft_strnstr(b, l, 16), strnstr(b, l, 16));
}

static void test_middle(void **state)
{
	const char *b = *state;
	const char *l = "42";

	assert_ptr_equal(ft_strnstr(b, l, 16), strnstr(b, l, 16));
}

static void test_end(void **state)
{
	const char *b = *state;
	const char *l = "Prague";

	assert_ptr_equal(ft_strnstr(b, l, 16), strnstr(b, l, 16));

}

static void test_not_found(void **state)
{
	const char *b = *state;
	const char *l = "world";

	assert_ptr_equal(ft_strnstr(b, l, 16), strnstr(b, l, 16));
	assert_null(ft_strnstr(b, l, 16));
}

// Return first match
static void test_multiple(void **state)
{
	const char *b = "42 Prague 42";
	const char *l = "42";

	(void)state;
	assert_ptr_equal(ft_strnstr(b, l, 12), strnstr(b, l, 12));
}

static void test_len_zero(void **state)
{
	const char *b = *state;
	const char *l = "Hello";

	assert_ptr_equal(ft_strnstr(b, l, 0), strnstr(b, l, 0));
	assert_null(ft_strnstr(b, l, 0));
}

static void test_len_one(void **state)
{
	const char *b = *state;
	const char *l = "Hello";

	assert_ptr_equal(ft_strnstr(b, l, 1), strnstr(b, l, 1));
	assert_null(ft_strnstr(b, l, 1));
}

// len = strlen(l)
static void test_len_exact(void **state)
{
	const char *b = *state;
	const char *l = "Hello";

	assert_ptr_equal(ft_strnstr(b, l, 5), strnstr(b, l, 5));
}

// len < strlen(l)
static void test_len_short(void **state)
{
	const char *b = *state;
	const char *l = "Hello";

	assert_ptr_equal(ft_strnstr(b, l, 4), strnstr(b, l, 4));
	assert_null(ft_strnstr(b, l, 4));
}

// 9 -> 42 se najde, 8 -> nenajde
static void test_len_boundary(void **state)
{
	const char *b = *state;
	const char *l = "42";

	assert_ptr_equal(ft_strnstr(b, l, 9), strnstr(b, l, 9));
	assert_ptr_equal(ft_strnstr(b, l, 8), strnstr(b, l, 8));
	assert_null(ft_strnstr(b, l, 8));
}

// cely match nemuze byt platny (nevejde se cely do len) => NULL
static void test_match_over_len(void **state)
{
	const char *b = *state;
	const char *l = "42 Prague";

	assert_ptr_equal(ft_strnstr(b, l, 9), strnstr(b, l, 9));
	assert_null(ft_strnstr(b, l, 9));
}

// ma vratit big
static void test_little_empty(void **state)
{
	const char *b = *state;
	const char *l = "";

	assert_ptr_equal(ft_strnstr(b, l, 0), strnstr(b, l, 0));
	assert_ptr_equal(ft_strnstr(b, l, 16), strnstr(b, l, 16));
}

// vraci NULL
static void test_big_empty(void **state)
{
	const char *b = "";
	const char *l = "Hello";

	(void)state;
	assert_ptr_equal(ft_strnstr(b, l, 16), strnstr(b, l, 16));
}

// vraci big
static void test_both_empty(void **state)
{
	const char *b = "";
	const char *l = "";

	(void)state;
	assert_ptr_equal(ft_strnstr(b, l, 0), strnstr(b, l, 0));
	assert_ptr_equal(ft_strnstr(b, l, 2), strnstr(b, l, 2));
}

// little longer then big
static void test_little_longer(void **state)
{
	const char *b = "Hello";
	const char *l = "Hello, world";

	(void)state;
	assert_ptr_equal(ft_strnstr(b, l, 16), strnstr(b, l, 16));
	assert_null(ft_strnstr(b, l, 16));
}

// little and big same length
static void test_same_length(void **state)
{
	const char *b = "Hello";
	const char *l1 = "Hello";
	const char *l2 = "Hallo";

	(void)state;
	assert_ptr_equal(ft_strnstr(b, l1, 5), strnstr(b, l1, 5));
	assert_ptr_equal(ft_strnstr(b, l2, 5), strnstr(b, l2, 5));
	assert_null(ft_strnstr(b, l2, 5));
}

// space in little
static void test_spaces(void **state)
{
	const char *b = *state;
	const char *l = "42 Prague";

	assert_ptr_equal(ft_strnstr(b, l, 16), strnstr(b, l, 16));
}

static void test_special_chars(void **state)
{
	const char *b = "Hello! @42 #Prague";
	const char *l = "@42";

	(void)state;
	assert_ptr_equal(ft_strnstr(b, l, 18), strnstr(b, l, 18));
}

// Hello vs hello
static void test_case_sensitive(void **state)
{
	const char *b = *state;
	const char *l = "hello";

	assert_ptr_equal(ft_strnstr(b, l, 16), strnstr(b, l, 16));
}

// pointer ukazuje na spravne misto
static void test_pointer(void **state)
{
	const char *b = *state;
	const char *l = "42";

	assert_ptr_equal(ft_strnstr(b, l, 16), b + 7);
}

int main(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_start),
		cmocka_unit_test(test_middle),
		cmocka_unit_test(test_end),
		cmocka_unit_test(test_not_found),
		cmocka_unit_test(test_multiple),
		cmocka_unit_test(test_len_zero),
		cmocka_unit_test(test_len_one),
		cmocka_unit_test(test_len_exact),
		cmocka_unit_test(test_len_short),
		cmocka_unit_test(test_len_boundary),
		cmocka_unit_test(test_match_over_len),
		cmocka_unit_test(test_little_empty),
		cmocka_unit_test(test_big_empty),
		cmocka_unit_test(test_both_empty),
		cmocka_unit_test(test_little_longer),
		cmocka_unit_test(test_same_length),
		cmocka_unit_test(test_spaces),
		cmocka_unit_test(test_special_chars),
		cmocka_unit_test(test_case_sensitive),
		cmocka_unit_test(test_pointer),
	};

	return cmocka_run_group_tests(tests, setup, NULL);
}
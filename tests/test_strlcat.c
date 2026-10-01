#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <bsd/string.h>
#include "libft.h"
#include <stdio.h>

// Velikost
//      size == 0 ✅
//      size < strlen(dest) ✅
//      size == strlen(dest) ✅
//		size == strlen(dest) + 1 ✅
//      strlen(dest) < size < strlen(dest) + strlen(src) + 1 ✅
//      size == strlen(dest) + strlen(src) + 1 ✅
//      size > strlen(dest) + strlen(src) + 1 ✅
//
// Prázdné řetězce
//      dest == "" ✅
//      src == "" ✅
//      dest == "" && src == "" ✅
//
// Návratová hodnota
//      pokud size > strlen(dest): strlen(dest) + strlen(src) ✅
//      pokud size <= strlen(dest): size + strlen(src) ✅


// size > strlen(dest) + strlen(src) + 1 
static void test_basic(void **state)
{
	char		dest[32] = "Hello, ";
	char 		ref[32] = "Hello, ";
	const char	*src = "42 Prague";

	(void)state;
	assert_int_equal(ft_strlcat(dest, src, sizeof(dest)), 
		strlcat(ref, src, sizeof(ref)));
	assert_string_equal(dest, ref);
}

// size = strlen(dest): Nepripoji se nic
static void test_size_equal_dest_len(void **state)
{
	char		dest[8] = "Hello, ";
	char		ref[8] = "Hello, ";
	const char	*src = "42 Prague";

	(void)state;
	assert_int_equal(ft_strlcat(dest, src, 7), strlcat(ref, src, 7));
	assert_memory_equal(dest, ref, 7);
}

// size = strlen(dest) + 1: v bufferu je dest + '\0' => nepripoji se nic
static void test_size_dest_len_plus_one(void **state)
{
	char		dest[8] = "Hello, ";
	char		ref[8] = "Hello, ";
	const char	*src = "42 Prague";

	(void)state;
	assert_int_equal(ft_strlcat(dest, src, 8), strlcat(ref, src, 8));
	assert_memory_equal(dest, ref, 8);
	assert_int_equal(dest[7], '\0');
}

// strlen(dest) < size < strlen(dest) + strlen(src) + 1: src se nevejde cele
static void test_partial_copy(void **state)
{
	char		dest[32] = "Hello, ";
	char		ref[32] = "Hello, ";
	const char	*src = "42 Prague";

	(void)state;
	assert_int_equal(ft_strlcat(dest, src, 12), strlcat(ref, src, 12));
	assert_string_equal(dest, ref);
	assert_int_equal(dest[11], '\0');
}

// size = strlen(dest) + strlen(src) + 1
static void test_exact_size(void **state)
{
	char		dest[32] = "Hello, ";
	char		ref[32] = "Hello, ";
	const char	*src = "42 Prague";

	(void)state;
	assert_int_equal(ft_strlcat(dest, src, 17), strlcat(ref, src, 17));
	assert_string_equal(dest, ref);
	assert_int_equal(dest[16], '\0');
}

// size == 0: nesmi se zmenit nic
static void test_size_zero(void **state)
{
	char		dest[32] = "Hello, ";
	char		ref[32] = "Hello, ";
	const char	*src = "42 Prague";	

	(void)state;
	assert_int_equal(ft_strlcat(dest, src, 0), strlcat(ref, src, 0));
	assert_memory_equal(dest, ref, sizeof(dest));
}

static void test_empty_src(void **state)
{
	char		dest[32] = "Hello, ";
	char		ref[32] = "Hello, ";
	const char	*src = "";

	(void)state;
	assert_int_equal(ft_strlcat(dest, src, sizeof(dest)), 
		strlcat(ref, src, sizeof(ref)));
	assert_string_equal(dest, ref);
}

static void test_empty_dest(void **state)
{
	char		dest[32] = "";
	char		ref[32] = "";
	const char	*src = "42 Prague";

	(void)state;
	assert_int_equal(ft_strlcat(dest, src, sizeof(dest)), 
		strlcat(ref, src, sizeof(ref)));
	assert_string_equal(dest, ref);
}

// size < strlen(dest): src se nepripoji, dest se nezmeni
static void test_size_smaller_than_dest_len(void **state)
{
	char		dest[32] = "Hello, ";
	char		ref[32] = "Hello, ";
	const char	*src = "42 Prague";

	(void)state;
	assert_int_equal(ft_strlcat(dest, src, 5), strlcat(ref, src, 5));
	assert_memory_equal(dest, ref, sizeof(dest));
}

static void test_return_value(void **state)
{
	char		dest[32] = "Hello, ";
	const char	*src = "42 Prague";
	size_t		dest_len;
	size_t		src_len;

	(void)state;
	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	assert_int_equal(ft_strlcat(dest, src, sizeof(dest)), dest_len + src_len);
}

static void test_return_value_size_smaller_than_dest(void **state)
{
	char		dest[32] = "Hello, ";
	const char	*src = "42 Prague";

	(void)state;
	assert_int_equal(ft_strlcat(dest, src, 5), ft_strlen(src) + 5);
}

static void test_empty_dest_and_src(void **state)
{
	char		dest[32] = "";
	char		ref[32] = "";
	const char	*src = "";

	(void)state;
	assert_int_equal(ft_strlcat(dest, src, sizeof(dest)), 
		strlcat(ref, src, sizeof(ref)));
	assert_string_equal(dest, ref);
}

int main(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_basic),
		cmocka_unit_test(test_size_equal_dest_len),
		cmocka_unit_test(test_size_dest_len_plus_one),
		cmocka_unit_test(test_partial_copy),
		cmocka_unit_test(test_exact_size),
		cmocka_unit_test(test_size_zero),
		cmocka_unit_test(test_empty_src),
		cmocka_unit_test(test_empty_dest),
		cmocka_unit_test(test_size_smaller_than_dest_len),
		cmocka_unit_test(test_return_value),
		cmocka_unit_test(test_return_value_size_smaller_than_dest),
		cmocka_unit_test(test_empty_dest_and_src),
	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}
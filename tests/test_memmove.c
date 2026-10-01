#include "libft.h"
#include <cmocka.h>
#include <string.h>

static void	assert_memmove(void *dst, void *oracle, const void *src, size_t n)
{
	memmove(oracle, src, n);
	ft_memmove(dst, src, n);
	assert_memory_equal(dst, oracle, n);
}

static void	test_basic(void **state)
{
	char	dst[20] = {0};
	char	oracle[20] = {0};
	char	src[] = "Hello, 42!";

	(void)state;
	assert_memmove(dst, oracle, src, sizeof(src));
}

static void	test_partial(void **state)
{
	char	dst[20] = {0};
	char	oracle[20] = {0};
	char	src[] = "Hello, 42!";

	(void)state;
	assert_memmove(dst, oracle, src, 5);
}

static void	test_zero(void **state)
{
	char	dst[20] = {0};
	char	oracle[20] = {0};
	char	src[] = "Hello, 42!";

	(void)state;
	assert_memmove(dst, oracle, src, 0);
}

static void	test_overlap_shift_to_right(void **state)
{
	char	dst[20] = "0123456789";
	char	oracle[20] = "0123456789";

	(void)state;
	memmove(oracle + 2, oracle, 8);
	ft_memmove(dst + 2, dst, 8);
	assert_memory_equal(dst, oracle, sizeof(dst));
	assert_memory_equal(dst, "0101234567", 11);
}

static void	test_overlap_shift_to_left(void **state)
{
	char	dst[20] = "0123456789";
	char	oracle[20] = "0123456789";

	(void)state;
	memmove(oracle, oracle + 2, 8);
	ft_memmove(dst, dst + 2, 8);
	assert_memory_equal(dst, oracle, sizeof(dst));
	assert_memory_equal(dst, "2345678989", 11);
}

static void	test_same_buffer(void **state)
{
	char	dst[20] = "0123456789";
	char	oracle[20] = "0123456789";

	(void)state;
	memmove(oracle, oracle, 10);
	ft_memmove(dst, dst, 10);
	assert_memory_equal(dst, oracle, sizeof(dst));
	assert_memory_equal(dst, "0123456789", 11);
}

static void	test_binary(void **state)
{
	unsigned char	dst[5] = {0};
	unsigned char	oracle[5] = {0};
	unsigned char	src[] = {1, 0, 42, 255, 7};

	(void)state;
	memmove(oracle, src, sizeof(src));
	ft_memmove(dst, src, sizeof(src));
	assert_memory_equal(dst, oracle, sizeof(dst));
}

static void	test_overlap_one_right(void **state)
{
	char	dst[20] = "0123456789";
	char	oracle[20] = "0123456789";

	(void)state;
	memmove(oracle + 1, oracle, 9);
	ft_memmove(dst + 1, dst, 9);
	assert_memory_equal(dst, oracle, sizeof(dst));
	assert_memory_equal(dst, "0012345678", 11);
}

static void	test_overlap_one_left(void **state)
{
	char	dst[20] = "0123456789";
	char	oracle[20] = "0123456789";

	(void)state;
	memmove(oracle, oracle + 1, 9);
	ft_memmove(dst, dst + 1, 9);
	assert_memory_equal(dst, oracle, sizeof(dst));
	assert_memory_equal(dst, "1234567899", 11);
}

int main(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_basic),
		cmocka_unit_test(test_partial),
		cmocka_unit_test(test_zero),
		cmocka_unit_test(test_overlap_shift_to_right),
		cmocka_unit_test(test_overlap_shift_to_left),
		cmocka_unit_test(test_same_buffer),
		cmocka_unit_test(test_binary),
		cmocka_unit_test(test_overlap_one_right),
		cmocka_unit_test(test_overlap_one_left),
	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}
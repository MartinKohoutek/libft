#include "libft.h"
#include <cmocka.h>
#include <string.h>

static void	assert_memcpy(void *dst, void *oracle, const void *src, size_t n)
{
	memcpy(oracle, src, n);
	ft_memcpy(dst, src, n);
	assert_memory_equal(dst, oracle, n);
}

static void	test_basic(void **state)
{
	char	dst[20] = {0};
	char	oracle[20] = {0};
	char	src[] = "Hello, 42!";

	(void)state;
	assert_memcpy(dst, oracle, src, sizeof(src));
}

static void	test_partial(void **state)
{
	char	dst[20] = {0};
	char	oracle[20] = {0};
	char	src[] = "Hello, 42!";

	(void)state;
	assert_memcpy(dst, oracle, src, 5);
}

static void	test_zero(void **state)
{
	char	dst[20] = {0};
	char	oracle[20] = {0};
	char	src[] = "Hello, 42!";

	(void)state;
	assert_memcpy(dst, oracle, src, 0);
}

static void	test_one(void **state)
{
	char	dst[20] = {0};
	char	oracle[20] = {0};
	char	src[] = "Hello, 42!";

	(void)state;
	assert_memcpy(dst, oracle, src, 1);
}

static void	test_binary_data(void **state)
{
	unsigned char	dst[5] = {0};
	unsigned char	oracle[5] = {0};
	unsigned char	src[] = {1, 0, 42, 255, 7};

	(void)state;
	assert_memcpy(dst, oracle, src, sizeof(src));
}

static void	test_overwrite(void **state)
{
	char	dst[10] = "XXXXXXXXX";
	char	oracle[10] = "XXXXXXXXX";
	char	src[] = "ABC";

	(void)state;
	assert_memcpy(dst, oracle, src, sizeof(src));
}

int main(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_basic),
		cmocka_unit_test(test_partial),
		cmocka_unit_test(test_zero),
		cmocka_unit_test(test_one),
		cmocka_unit_test(test_binary_data),
		cmocka_unit_test(test_overwrite),
	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}
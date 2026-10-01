#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include "libft.h"

static void even(unsigned int i, char *c)
{
	if (i % 2 == 0)
		*c = 'E';
}

static void	test_basic(void **state)
{
	char	s[] = "abcdef";

	(void)state;
	ft_striteri(s, even);
	assert_string_equal(s, "EbEdEf");
}

static void	test_one(void **state)
{
	char	s[] = "a";

	(void)state;
	ft_striteri(s, even);
	assert_string_equal(s, "E");
}

static void	test_empty(void **state)
{
	char	s[] = "";

	(void)state;
	ft_striteri(s, even);
	assert_string_equal(s, "");
}

static void	test_null(void **state)
{
	(void)state;
	ft_striteri(NULL, even);
}

int main(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_basic),
		cmocka_unit_test(test_one),
		cmocka_unit_test(test_empty),
		cmocka_unit_test(test_null),
		
	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}
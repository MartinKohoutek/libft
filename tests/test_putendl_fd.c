#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "libft.h"

static void	assert_putendl_fd(const char *s)
{
	int		pipefd[2];
	char	res[100];
	size_t	len;

	len = strlen(s);
	pipe(pipefd);
	ft_putendl_fd((char *)s, pipefd[1]);
	close(pipefd[1]);
	read(pipefd[0], res, len + 1);
	close(pipefd[0]);
	assert_memory_equal(res, s, len);
	assert_int_equal(res[len], '\n');
}

static void	test_basic(void **state)
{
	(void)state;
	assert_putendl_fd("Hello");
	assert_putendl_fd("42");
	assert_putendl_fd("Hello, 42 Prague!");
}

static void	test_empty(void **state)
{
	(void)state;
	assert_putendl_fd("");
}

static void	test_special_chars(void **state)
{
	(void)state;
	assert_putendl_fd("\t");
	assert_putendl_fd("\n");
	assert_putendl_fd("Hello\n42");
	assert_putendl_fd("Hello\t42");
}

static void	test_multiple(void **state)
{
	int		pipefd[2];
	char	res[11];

	(void)state;
	pipe(pipefd);
	ft_putendl_fd("Hello", pipefd[1]);
	ft_putendl_fd("42", pipefd[1]);
	ft_putendl_fd("!", pipefd[1]);
	close(pipefd[1]);
	read(pipefd[0], res, 11);
	close(pipefd[0]);
	assert_memory_equal(res, "Hello\n42\n!\n", 11);
}

static void	test_different_fds(void **state)
{
	int		pipe1[2];
	int		pipe2[2];
	char	res1[3];
	char	res2[3];

	(void)state;
	pipe(pipe1);
	pipe(pipe2);
	ft_putendl_fd("A", pipe1[1]);
	ft_putendl_fd("B", pipe2[1]);
	close(pipe1[1]);
	close(pipe2[1]);
	read(pipe1[0], res1, 2);
	read(pipe2[0], res2, 2);
	close(pipe1[0]);
	close(pipe2[0]);
	assert_memory_equal(res1, "A\n", 2);
	assert_memory_equal(res2, "B\n", 2);
}

int main(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_basic),
		cmocka_unit_test(test_empty),
		cmocka_unit_test(test_special_chars),
		cmocka_unit_test(test_multiple),
		cmocka_unit_test(test_different_fds),
	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}
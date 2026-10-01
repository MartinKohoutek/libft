#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "libft.h"

static void	assert_putstr_fd(const char *s)
{
	int		pipefd[2];
	char	res[100];
	ssize_t	n;

	pipe(pipefd);
	ft_putstr_fd((char *)s, pipefd[1]);
	close(pipefd[1]);
	n = read(pipefd[0], res, sizeof(res));
	close(pipefd[0]);
	assert_int_equal(n, strlen(s));
	assert_memory_equal(res, s, strlen(s));
}

static void	test_basic(void **state)
{
	(void)state;
	assert_putstr_fd("Hello");
	assert_putstr_fd("42");
	assert_putstr_fd("Hello, 42 Prague!");
}

static void	test_empty(void **state)
{
	(void)state;
	assert_putstr_fd("");
}

static void	test_special_chars(void **state)
{
	(void)state;
	assert_putstr_fd("\n");
	assert_putstr_fd("\t");
	assert_putstr_fd("Hello\n42");
}

static void	test_multiple(void **state)
{
	int		pipefd[2];
	char	res[9];

	(void)state;
	pipe(pipefd);
	ft_putstr_fd("Hello", pipefd[1]);
	ft_putstr_fd("42", pipefd[1]);
	ft_putstr_fd("!", pipefd[1]);
	close(pipefd[1]);
	read(pipefd[0], res, 8);
	close(pipefd[0]);
	assert_memory_equal(res, "Hello42!", 8);
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
	ft_putstr_fd("AA", pipe1[1]);
	ft_putstr_fd("BB", pipe2[1]);
	close(pipe1[1]);
	close(pipe2[1]);
	read(pipe1[0], res1, 2);
	read(pipe2[0], res2, 2);
	close(pipe1[0]);
	close(pipe2[0]);
	assert_memory_equal(res1, "AA", 2);
	assert_memory_equal(res2, "BB", 2);
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
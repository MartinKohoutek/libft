#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "libft.h"

static void assert_putchar_fd(char c)
{
	int		pipefd[2];
	char	res;

	pipe(pipefd);
	ft_putchar_fd(c, pipefd[1]);
	close(pipefd[1]);
	read(pipefd[0], &res, 1);
	close(pipefd[0]);
	assert_int_equal(res, c);
}

static void test_basic(void **state)
{
	(void)state;
	assert_putchar_fd('A');
	assert_putchar_fd('a');
	assert_putchar_fd('0');
	assert_putchar_fd(' ');
	assert_putchar_fd('!');
}

static void test_borders(void **state)
{
	(void)state;
	assert_putchar_fd('\0');
	assert_putchar_fd('\n');
	assert_putchar_fd('\t');
}

static void test_multiple(void **state)
{
	int		pipefd[2];
	char	res[3];

	(void)state;
	pipe(pipefd);
	ft_putchar_fd('A', pipefd[1]);
	ft_putchar_fd('B', pipefd[1]);
	ft_putchar_fd('C', pipefd[1]);
	close(pipefd[1]);
	read(pipefd[0], res, 3);
	close(pipefd[0]);
	assert_memory_equal(res, "ABC", 3);
}

static void	test_different_fds(void **state)
{
	int		pipe1[2];
	int		pipe2[2];
	char	c1;
	char	c2;

	(void)state;
	pipe(pipe1);
	pipe(pipe2);
	ft_putchar_fd('A', pipe1[1]);
	ft_putchar_fd('B', pipe2[1]);
	close(pipe1[1]);
	close(pipe2[1]);
	read(pipe1[0], &c1, 1);
	read(pipe2[0], &c2, 1);
	close(pipe1[0]);
	close(pipe2[0]);
	assert_int_equal(c1, 'A');
	assert_int_equal(c2, 'B');
}

int main(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_basic),
		cmocka_unit_test(test_borders),
		cmocka_unit_test(test_multiple),
		cmocka_unit_test(test_different_fds),
	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}
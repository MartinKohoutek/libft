#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include "libft.h"

static void	assert_putnbr_fd(int n)
{
	int		pipefd[2];
	char	res[100];
	char	expected[100];
	ssize_t	len;

	len = snprintf(expected, sizeof(expected), "%d", n);
	pipe(pipefd);
	ft_putnbr_fd(n, pipefd[1]);
	close(pipefd[1]);
	assert_int_equal(read(pipefd[0], res, sizeof(res)), len);
	close(pipefd[0]);
	assert_memory_equal(res, expected, len);
}

static void	test_basic(void **state)
{
	(void)state;
	assert_putnbr_fd(0);
	assert_putnbr_fd(1);
	assert_putnbr_fd(-1);
	assert_putnbr_fd(42);
	assert_putnbr_fd(-42);
	assert_putnbr_fd(123456);
	assert_putnbr_fd(-123456);
}

static void	test_borders(void **state)
{
	(void)state;
	assert_putnbr_fd(INT_MAX);
	assert_putnbr_fd(INT_MIN);
}

static void	test_powers(void **state)
{
	(void)state;
	assert_putnbr_fd(9);
	assert_putnbr_fd(10);
	assert_putnbr_fd(99);
	assert_putnbr_fd(100);
	assert_putnbr_fd(-9);
	assert_putnbr_fd(-10);
	assert_putnbr_fd(-99);
	assert_putnbr_fd(-100);
}

static void	test_multiple(void **state)
{
	int		pipefd[2];
	char	res[20];

	(void)state;
	pipe(pipefd);
	ft_putnbr_fd(42, pipefd[1]);
	ft_putnbr_fd(-7, pipefd[1]);
	ft_putnbr_fd(0, pipefd[1]);
	close(pipefd[1]);
	read(pipefd[0], res, 20);
	close(pipefd[0]);
	assert_memory_equal(res, "42-70", 5);
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
	ft_putnbr_fd(42, pipe1[1]);
	ft_putnbr_fd(-7, pipe2[1]);
	close(pipe1[1]);
	close(pipe2[1]);
	read(pipe1[0], res1, 2);
	read(pipe2[0], res2, 2);
	close(pipe1[0]);
	close(pipe2[0]);
	assert_memory_equal(res1, "42", 2);
	assert_memory_equal(res2, "-7", 2);
}

int main(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_basic),
		cmocka_unit_test(test_borders),
		cmocka_unit_test(test_powers),
		cmocka_unit_test(test_multiple),
		cmocka_unit_test(test_different_fds),
	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}
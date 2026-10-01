#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include <string.h>
#include "libft.h"

#define BUFFER_SIZE 20
#define TEST_STRING "Hello, 42 Prague"

static void test_memset(int c, size_t n)
{
	char	buffer[BUFFER_SIZE] = TEST_STRING;
	char	oracle[BUFFER_SIZE] = TEST_STRING;

	ft_memset(buffer, c, n);
	memset(oracle, c, n);
	assert_memory_equal(buffer, oracle, sizeof(buffer));
}

static void test_basic(void **state)
{
	(void)state;
	test_memset(0, BUFFER_SIZE);
	test_memset('A', BUFFER_SIZE);
	test_memset('x', BUFFER_SIZE);
	test_memset('0', BUFFER_SIZE);
	test_memset(' ', BUFFER_SIZE);
}

// Buffer se nesmi zmenit
static void test_zero_n(void **state)
{
	(void)state;
	test_memset('X', 0);
}

// Zmeni se 1 bajt, zbytek bufferu se nezmeni
static void test_one_n(void **state)
{
	(void)state;
	test_memset('X', 1);
}

static void test_small_n(void **state)
{
	(void)state;
	test_memset('X', BUFFER_SIZE / 2);
}

// memset neresi kde je konec stringu, '\0' ho nezajima
// Zmeni presne BUFFER_SIZE - 2 bajtu
// Posledni 2 bajty se nesmi zmenit
static void test_after_null(void **state)
{
	(void)state;
	test_memset('X', BUFFER_SIZE - 2);
}

// memset bere int, ale zapisuje jen nejnizsi byte
static void test_byte_value(void **state)
{
	(void)state;
	test_memset(0x100, BUFFER_SIZE);		// ulozi jen 00
	test_memset(0x123, BUFFER_SIZE);		// ulozi jen 23
	test_memset(-1, BUFFER_SIZE);			// ulozi FF
	test_memset(-2, BUFFER_SIZE);			// ulozi FE
	test_memset(0x7F, BUFFER_SIZE);			// 7F
	test_memset(0x80, BUFFER_SIZE);			// 80 (128 dec);
}

// porovnej ukazatel na buffer a vraceny ukazatel
static void test_return(void **state)
{
	char	buffer[BUFFER_SIZE] = TEST_STRING;

	(void)state;
	assert_ptr_equal(ft_memset(buffer, 'X', BUFFER_SIZE), buffer);
}

int main(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_basic),
		cmocka_unit_test(test_zero_n),
		cmocka_unit_test(test_one_n),
		cmocka_unit_test(test_small_n),
		cmocka_unit_test(test_after_null),
		cmocka_unit_test(test_byte_value),
		cmocka_unit_test(test_return),
	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}
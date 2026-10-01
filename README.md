*This project has been created as part of the 42 curriculum by mkohoute@student.42.fr.*

# Libft

## Description

**Libft** is the first project of the 42 Core Curriculum.

The goal of this project is to create a personal C library containing a set of commonly used functions from the standard C library, together with additional utility functions commonly used throughout the 42 curriculum.

Instead of relying directly on existing implementations, the project requires the functions to be implemented from scratch while following the constraints imposed by the 42 Norm and the project subject.

The resulting library is built as a static archive:

```text
libft.a
```

The project contains **43 functions**, covering:

- character classification and conversion
- string manipulation
- memory manipulation
- conversion and allocation utilities
- file-descriptor output functions
- linked-list manipulation

The library is designed to be reusable in later 42 projects.

## Library

### Character checks and conversions

| Function | Description |
|---|---|
| `ft_isalpha` | Checks whether a character is alphabetic. |
| `ft_isdigit` | Checks whether a character is a decimal digit. |
| `ft_isalnum` | Checks whether a character is alphanumeric. |
| `ft_isascii` | Checks whether a character belongs to the ASCII character set. |
| `ft_isprint` | Checks whether a character is printable. |
| `ft_toupper` | Converts a lowercase character to uppercase. |
| `ft_tolower` | Converts an uppercase character to lowercase. |

### Memory functions

| Function | Description |
|---|---|
| `ft_memset` | Fills a memory area with a specified byte. |
| `ft_bzero` | Sets a memory area to zero. |
| `ft_memcpy` | Copies a block of memory. |
| `ft_memmove` | Copies memory while handling overlapping areas safely. |
| `ft_memchr` | Searches a memory area for a byte. |
| `ft_memcmp` | Compares two memory areas. |
| `ft_calloc` | Allocates and zero-initializes memory. |

### String functions

| Function | Description |
|---|---|
| `ft_strlen` | Returns the length of a string. |
| `ft_strchr` | Locates the first occurrence of a character in a string. |
| `ft_strrchr` | Locates the last occurrence of a character in a string. |
| `ft_strncmp` | Compares two strings up to a specified number of characters. |
| `ft_strnstr` | Searches for a substring within a string with a length limit. |
| `ft_strlcpy` | Copies a string into a size-limited buffer. |
| `ft_strlcat` | Appends a string to a size-limited destination buffer. |
| `ft_strdup` | Duplicates a string using dynamic allocation. |
| `ft_substr` | Creates a substring from a string. |
| `ft_strjoin` | Concatenates two strings into a newly allocated string. |
| `ft_strtrim` | Removes specified characters from the beginning and end of a string. |
| `ft_split` | Splits a string into an array of strings using a delimiter. |
| `ft_strjoin` | Concatenates two strings into a newly allocated string. |

### Conversion

| Function | Description |
|---|---|
| `ft_atoi` | Converts the initial part of a string to an integer. |
| `ft_itoa` | Converts an integer to a dynamically allocated string. |

### File-descriptor output

| Function | Description |
|---|---|
| `ft_putchar_fd` | Writes a character to a file descriptor. |
| `ft_putstr_fd` | Writes a string to a file descriptor. |
| `ft_putendl_fd` | Writes a string followed by a newline to a file descriptor. |
| `ft_putnbr_fd` | Writes an integer to a file descriptor. |

### Function application

| Function | Description |
|---|---|
| `ft_striteri` | Applies a function to every character of a string, providing its index. |
| `ft_strmapi` | Creates a new string by applying a function to every character. |

### Linked lists

The project uses the following list structure:

```c
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;
```

| Function | Description |
|---|---|
| `ft_lstnew` | Creates a new list element. |
| `ft_lstadd_front` | Adds an element to the beginning of a list. |
| `ft_lstsize` | Returns the number of elements in a list. |
| `ft_lstlast` | Returns the last element of a list. |
| `ft_lstadd_back` | Adds an element to the end of a list. |
| `ft_lstdelone` | Deletes one list element using a supplied deletion function. |
| `ft_lstclear` | Deletes an entire list. |
| `ft_lstiter` | Applies a function to every list element. |
| `ft_lstmap` | Creates a new list by applying a function to every element. |

## Technical Choices

The library is implemented in C and built as a static archive using `make`.

The implementation follows the constraints of the 42 curriculum, including the 42 coding standard (Norm).

Particular attention is given to:

- correct handling of boundary conditions
- dynamic memory allocation and cleanup
- overlapping memory regions in `ft_memmove`
- integer overflow in `ft_calloc`
- `INT_MIN` handling in `ft_itoa`
- empty strings and zero-length operations
- `NULL` input where permitted by the subject
- correct behavior with file descriptors
- linked-list ownership and deletion callbacks

## Instructions

### Building the library

From the repository root:

```bash
make
```

This creates:

```text
libft.a
```

### Cleaning object files

```bash
make clean
```

### Removing all generated files

```bash
make fclean
```

### Rebuilding

```bash
make re
```

### Using the library

Include the library header:

```c
#include "libft.h"
```

Compile your program together with the library:

```bash
cc main.c -L. -lft
```

Or explicitly provide the archive:

```bash
cc main.c libft.a
```

## Resources

### C and standard library references

- ISO/IEC 9899 — The C Standard
- `man 3` documentation for the corresponding standard library functions
- GNU C Library documentation
- Linux manual pages

Useful manual pages include:

```bash
man 3 malloc
man 3 calloc
man 3 memcpy
man 3 memmove
man 3 strlen
man 3 strchr
man 3 strncmp
```

### AI usage

AI tools were used as a development and learning aid during the project.

They were primarily used for:

- discussing possible implementation approaches
- explaining C language and pointer concepts
- reviewing algorithms and edge cases
- designing and reviewing unit tests
- identifying missing test cases
- debugging test failures
- discussing memory allocation and failure handling
- improving the test runner and Makefile
- discussing CMocka usage
- reviewing the README and project documentation

AI was not used as a replacement for understanding the implementations. The resulting code was reviewed, tested, modified and validated manually, including through the project's own test suite.

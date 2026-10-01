ROOT = ..
CMOCKA = libs/cmocka
BUILD = .build

CC = cc
CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -I$(ROOT) -I$(CMOCKA)/include
LDFLAGS = -L$(CMOCKA)/lib
LDLIBS = -lcmocka
LBSD = -lbsd

LWMALLOC = -Wl,--wrap=malloc
LWFREE = -Wl,--wrap=free

GREEN = \033[32m
RED = \033[31m
YELLOW = \033[33m
RESET = \033[0m

DETAIL = 0
VERBOSE = 0
Q = @

ifeq ($(VERBOSE),1)
Q =
endif

SANITIZE = 0

ifeq ($(SANITIZE),1)
SANITIZE_CFLAGS = -fsanitize=address,undefined -fno-omit-frame-pointer
SANITIZE_LDFLAGS = -fsanitize=address,undefined
endif

VALGRIND = 0

ifeq ($(VALGRIND),1)
VALGRIND_CMD = valgrind --leak-check=full --error-exitcode=1
else
VALGRIND_CMD =
endif

PEDANTIC = 0

ifeq ($(PEDANTIC),1)
PEDANTIC_CFLAGS = -pedantic
endif

ifeq ($(SANITIZE)$(VALGRIND),11)
$(error SANITIZE=1 and VALGRIND=1 cannot be used together)
endif

TESTS = bzero isalnum isalpha isascii isdigit isprint strlen split itoa \
	lstadd_back lstadd_front lstiter lstlast lstmap \
	lstnew lstsize memset strlcat strlcpy strncmp strnstr \
	strtrim substr tolower toupper memcpy memmove memchr memcmp strchr \
	atoi putstr_fd putchar_fd putendl_fd putnbr_fd striteri strmapi \
	lstclear lstdelone strrchr strdup calloc strjoin

BSD = bzero strnstr

WMALLOC = split lstnew strtrim substr strmapi strdup calloc strjoin
WFREE = split lstclear lstdelone

all: test

test:
	@$(MAKE) --no-print-directory -C $(ROOT) && \
	rm -f $(BUILD)/status-* && \
	for test in $(TESTS); do \
		$(MAKE) --no-print-directory run-$$test; \
	done; \
	total=$$(printf '%s\n' $(TESTS) | wc -w); \
	tested=$$(grep -l '^OK\|^KO' $(BUILD)/status-* 2>/dev/null | wc -l); \
	skipped=$$(grep -l '^SKIP' $(BUILD)/status-* 2>/dev/null | wc -l); \
	tests=$$(grep '^TESTS ' $(BUILD)/status-* 2>/dev/null | \
		awk '{sum += $$2} END {print sum+0}'); \
	passed=$$(grep '^PASSED ' $(BUILD)/status-* 2>/dev/null | \
		awk '{sum += $$2} END {print sum+0}'); \
	failed=$$(grep '^FAILED ' $(BUILD)/status-* 2>/dev/null | \
		awk '{sum += $$2} END {print sum+0}'); \
	printf "\n=== Summary ===\n"; \
	printf "Tested          %s / %s functions\n" "$$tested" "$$total"; \
	printf "Total Tests     %s\n" "$$tests"; \
	printf "Passed          %s\n" "$$passed"; \
	printf "Failed          %s\n" "$$failed"; \
	printf "Skipped         %s\n" "$$skipped"; \
	if [ "$$failed" -eq 0 ]; then \
		printf "\n$(GREEN)All tests passed.$(RESET)\n"; \
	else \
		printf "\n$(RED)Some tests failed.$(RESET)\n"; \
	fi

run-%:
	@if nm -g --defined-only "$(ROOT)/libft.a" | \
		grep -qE "[[:space:]]ft_$*[[:space:]]*$$"; then \
		printf "\n========== %s ==========\n" "$*"; \
		mkdir -p $(BUILD); \
		rm -f $(BUILD)/status-$*; \
		if $(MAKE) --no-print-directory build-$* \
			>$(BUILD)/link.log 2>&1; then \
			if [ "$(VERBOSE)" = "1" ]; then \
				cat $(BUILD)/link.log; \
			fi; \
			if $(VALGRIND_CMD) $(BUILD)/test_$* >$(BUILD)/test.log 2>&1; then \
				if [ "$(DETAIL)" = "1" ]; then \
					cat $(BUILD)/test.log; \
				else \
					awk '/^\[/{ \
						if ($$2 == "OK") { \
							name = $$4; \
							sub(/^test_/, "", name); \
							gsub(/_/, " ", name); \
							printf "%s: %s test : $(GREEN)[OK]$(RESET)\n", \
								toupper("$*"), name; \
						} \
					}' $(BUILD)/test.log; \
				fi; \
				tests=$$(awk '/tests: [0-9]+ test\(s\) run/ {print $$3}' \
					$(BUILD)/test.log); \
				passed=$$(awk '/^\[  PASSED  \]/ {print $$4}' \
					$(BUILD)/test.log); \
				failed=$$(awk '/^\[  FAILED  \] tests:/ {print $$5}' \
					$(BUILD)/test.log); \
				printf "TESTS %s\n" "$${tests:-0}" \
					> $(BUILD)/status-$*; \
				printf "PASSED %s\n" "$${passed:-0}" \
					>> $(BUILD)/status-$*; \
				printf "FAILED %s\n" "$${failed:-0}" \
					>> $(BUILD)/status-$*; \
				printf "OK\n" >> $(BUILD)/status-$*; \
				printf "========== $(GREEN)[ OK ]$(RESET) %s ==========\n" "$*"; \
			else \
				cat $(BUILD)/test.log; \
				tests=$$(awk '/tests: [0-9]+ test\(s\) run/ {print $$3}' \
					$(BUILD)/test.log); \
				passed=$$(awk '/^\[  PASSED  \]/ {print $$4}' \
					$(BUILD)/test.log); \
				failed=$$(awk '/^\[  FAILED  \] tests:/ {print $$5}' \
					$(BUILD)/test.log); \
				printf "TESTS %s\n" "$${tests:-0}" \
					> $(BUILD)/status-$*; \
				printf "PASSED %s\n" "$${passed:-0}" \
					>> $(BUILD)/status-$*; \
				printf "FAILED %s\n" "$${failed:-0}" \
					>> $(BUILD)/status-$*; \
				printf "KO\n" >> $(BUILD)/status-$*; \
				printf "========== $(RED)[ KO ]$(RESET) %s ==========\n" "$*"; \
			fi; \
		else \
			error=$$(grep -o "undefined reference to .*" \
				$(BUILD)/link.log | head -1); \
			printf "$(YELLOW)[ link failed: %s ]$(RESET)\n" "$$error"; \
			printf "TESTS 0\nPASSED 0\nFAILED 0\nSKIP\n" \
				> $(BUILD)/status-$*; \
			printf "========== $(YELLOW)[ SKIP ]$(RESET) %s ==========\n" "$*"; \
			if [ "$(VERBOSE)" = "1" ]; then \
				cat $(BUILD)/link.log; \
			fi; \
		fi; \
	else \
		printf "\n========== %s ==========\n" "$*"; \
		printf "$(YELLOW)[ SKIP ]$(RESET) %s (not in libft.a)\n" "$*"; \
		printf "TESTS 0\nPASSED 0\nFAILED 0\nSKIP\n" \
			> $(BUILD)/status-$*; \
		printf "========== $(YELLOW)[ SKIP ]$(RESET) %s ==========\n" "$*"; \
	fi

build-%: | $(BUILD)
	$(Q)$(CC) $(CFLAGS) $(PEDANTIC_CFLAGS) $(SANITIZE_CFLAGS) $(CPPFLAGS) \
		test_$*.c \
		$(LDFLAGS) $(SANITIZE_LDFLAGS) \
		$(if $(filter $*,$(WMALLOC)),$(LWMALLOC)) \
		$(if $(filter $*,$(WFREE)),$(LWFREE)) \
		$(ROOT)/libft.a \
		$(LDLIBS) \
		$(if $(filter $*,$(BSD)),$(LBSD)) \
		-o $(BUILD)/test_$*

$(BUILD):
	mkdir -p $(BUILD)

clean:
	rm -rf $(BUILD)

fclean: clean
	rm -rf $(CMOCKA)

.PHONY: all test clean
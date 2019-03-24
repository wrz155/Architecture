
/*
	miniunit.h 文件

*/


#ifndef MINIUNIT_H
#define MINIUNIT_H

#define mu_assert(message, test) do { if (!(test)) return message; } while (0)

#define mu_run_test(test) do { char *message = test(); tests_run++; \
                                if (message) return message; } while (0)
extern int tests_run;

#endif









/* file minunit_example.c */

#include <stdio.h>
#include "miniunit.h"

int tests_run = 0;

int foo = 7;
int bar = 5;

static char * test_foo() {
	mu_assert("error, foo != 7", foo == 7);
	return 0;
}

static char * test_bar() {
	mu_assert("error, bar != 5", bar == 5);
	return 0;
}

static char * all_tests() {
	mu_run_test(test_foo);
	mu_run_test(test_bar);
	return 0;
}

int main(int argc, char **argv) {
	char *result = all_tests();
	if (result != 0) {
		printf("%s\n", result);
	}
	else {
		printf("ALL TESTS PASSED\n");
	}
	printf("Tests run: %d\n", tests_run);
	getchar();
	return result != 0;
}
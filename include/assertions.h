#pragma once
#include <stddef.h>

#define assert(expr) \
    ((!!(expr)) \
    ? assert_success (#expr, __FILE__, __LINE__) \
    : assert_fail (#expr, __FILE__, __LINE__))


void int_success(void);
void int_fail(void);
void reset_local_counts(void);
int get_local_fail(void);
int get_local_success(void);
int print_stats();

int assert_success(const char* expr, const char* file, size_t line);
int assert_fail(const char* expr, const char* file, size_t line);

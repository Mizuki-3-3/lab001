#ifndef ASSERTIONS_H
#define ASSERTIONS_H
#include <stdio.h>

#define assert(expr) \
    ((!!(expr)) \
    ? assert_success (#expr, __FILE__, __LINE__) \
    : assert_fail (#expr, __FILE__, __LINE__))


void int_success(void);
void int_fail(void);
void reset_local_counts(void);
size_t get_local_fail(void);
size_t get_local_success(void);


int assert_success(const char* expr, const char* file, size_t line);
int assert_fail(const char* expr, const char* file, size_t line);

#endif
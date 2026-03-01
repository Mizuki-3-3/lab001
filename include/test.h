#ifndef TESTING_H
#define TESTING_H

#include <stdio.h>
#include <stdlib.h>

typedef void (*test_func)();

typedef struct test{
    const char* name;
    test_func test;
    struct test* next;
}test;

void register_test(const char* name, test_func test);
void run_tests();
#endif
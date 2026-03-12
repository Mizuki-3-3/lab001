#include "test.h"
#include "vector.h"

void init_vector_tests(void);

int main(void) {
    init_vector_tests();
    run_test();
    print_stats();
    cleanup_tests();
    return 0;
}
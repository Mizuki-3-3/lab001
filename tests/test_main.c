#include "test.h"
#include "vector.h"

void init_vector_tests(void);

int main(void) {
    init_vector_tests();
    run_tests();
    free_tests();
    return 0;
}
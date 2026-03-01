#include "assertions.h"

static size_t success_count = 0;  //специалный тип данных, беззнаковый, вмещает столько сколько определенная операционка предоставляет
static size_t fail_count = 0;
static size_t success_count_local = 0;
static size_t fail_count_local = 0;

void int_success(){
    success_count++;success_count_local++;
}

void int_fail(){
    fail_count++;fail_count_local++;
}

size_t get_local_fail(void) {
    return fail_count_local;
}

size_t get_local_success(void) {
    return success_count_local;
}

void reset_local_counts() {
    success_count_local = 0;
    fail_count_local = 0;
}

int assert_fail(const char* expr, const char* file, size_t lineno) {
    inc_fail();
    fprintf(stderr, "\033[0;31mAssertion failed: %s at %s:%zu\033[0m\n", expr, file, lineno);
    return 0;
}

int assert_success(const char* expr, const char* file, size_t lineno){
    int_succes();
    return 1;
}
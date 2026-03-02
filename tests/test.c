#include "vector.h"
#include "test.h"
#include "assertions.h"

static test* head = NULL;
static test* tail = NULL;

void register_test(const char* name, test_func func){
    test* temp = malloc(sizeof(test));
    temp->name = name;
    temp->func = func;
    temp->next = NULL;
    if ((!head)&&(!tail)){
        head = temp;
        tail = temp;
        return;
    }
    tail->next = temp;
    tail = temp;
}

void run_tests(void) {
    test* current = head;
    size_t total_passed = 0;
    size_t total_failed = 0;

    while (current) {
        printf("Running test: %s\n", current->name);
        reset_local_counts();          // обнуляем счётчики для текущего теста
        current->func();                // запускаем тест
        size_t passed = get_local_success();
        size_t failed = get_local_fail();
        total_passed += passed;
        total_failed += failed;
        if (!(failed))
            printf("  \033[0;32mPASSED\033[0m (assertions: %zu passed)\n", passed);
        else
            printf("  \033[0;31mFAILED\033[0m (assertions: %zu passed, %zu failed)\n", passed, failed);
        current = current->next;
    }
    printf("\nTotal: %zu tests, %zu passed, %zu failed\n",
           total_passed + total_failed, total_passed, total_failed);
}

void free_tests(void) {
    test* current = head;
    while (current) {
        test* next = current->next;
        free(current);
        current = next;
    }
    head = tail = NULL;
}

//покрыть все const тестами, проверка что не меняются
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
    int passed = 0;
    int total = 0;
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
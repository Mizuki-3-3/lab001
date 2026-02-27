#include "vector.h"
#include "test.h"

static test* head = NULL;
static test* tail = NULL;

void register_test(const char* name, test_func testf){
    test* temp = malloc(sizeof(test));
    temp->name = name;
    temp->test = testf;
    temp->next = NULL;
    if ((!head)&&(!tail)){
        head = temp;
        tail = temp;
        return;
    }
    tail->next = temp;
    tail = temp;
}


//покрыть все const тестами, проверка что не меняются
#include "assertions.h"

static size_t succes_count = 0;  //специалный тип данных, беззнаковый, вмещает столько сколько определенная операционка предоставляет
static size_t fail_count = 0;
static size_t succes_count_local = 0;
static size_t fail_count_local = 0;

void int_succes(){
    succes_count++;succes_count_local++;
}

void int_fail(){
    fail_count++;fail_count_local++;
}

int assert_fail(const char* expr, const char* file, size_t lineno){
    fprintf(stderr, "\033[0;32]");
    return;
}

int assert_secces(const char* expr, const char* file, size_t lineno){

}
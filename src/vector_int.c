#include "vector.h"

static field_info* int_field_info = NULL;

field_info* create_int_field_info(){
    field_info* temp = (field_info*)malloc(sizeof(field_info));
    if (!temp){
        return;
    }
    temp->add = add_int;
    temp->multip = multip_int;
    return temp;
}

field_info* get_int_field_info() {
    if (!int_field_info) {
        int_field_info = create_int_field_info();
    }
    return int_field_info;
}//можем нули возвращать надо подумать как фиксить

vector* add_int(const vector* a, const vector* b){
    if(!types_is_equal(a, b)){return;}
    vector* result = (vector*)malloc(sizeof(vector));
    int* new_x = malloc(sizeof(int));
    int* new_y = malloc(sizeof(int));
    if (!result || !new_x || !new_y){
        free(new_x); free(new_y); free(result);
        return NULL;
    }
    *new_x = *(int*)(a->x) + *(int*)(b->x);
    *new_y = *(int*)(a->y) + *(int*)(b->y);
    result->x = new_x;
    result->y = new_y;
    return (void*)result;
}

int multip_int(vector* a, vector* b){
    if(!types_is_equal(a, b)){return;}
    int result;
    result = (*(int*)a->x)*(*(int*)b->x) + (*(int*)a->y)*(*(int*)b->y);
    return result;
}

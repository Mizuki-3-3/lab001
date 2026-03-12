#include "vector.h"

static field_info* int_field_info = NULL;

field_info* get_int_field_info() {
    if (!int_field_info) {
        int_field_info = create_int_field_info();
    }
    return int_field_info;
}//можем нули возвращать надо подумать как фиксить

field_info* create_int_field_info(){
    field_info* temp = (field_info*)malloc(sizeof(field_info));
    if (!temp){
        return NULL;
    }
    temp->add = add_int;
    temp->multip = multip_int;
    return temp;
}

int types_are_int(const vector* a, const vector* b){
    return (a->info == int_field_info && b->info == int_field_info);
}

vector* add_int(const vector* a, const vector* b){
    if(!types_are_int(a, b)){return NULL;}
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
    result->info = get_int_field_info();
    return (void*)result;
}

int multip_int(const vector* a, const vector* b, void* result){
    if(!types_are_int(a, b)){return 0;}
    *(int*)result = (*(int*)a->x)*(*(int*)b->x) + (*(int*)a->y)*(*(int*)b->y);
    return 1;
}

int is_equal_int(const vector* a, const vector* b){
    if (!types_are_int(a,b)){return -1;}
    return (*(int*)(a->x)==*(int*)(b->x)&&*(int*)(a->y)==*(int*)(b->y));
}
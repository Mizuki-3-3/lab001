#include "vector.h"

static field_info* double_field_info = NULL;

field_info* get_double_field_info() {
    if (!double_field_info) {
        double_field_info = create_double_field_info();
    }
    return double_field_info;
}
field_info* create_double_field_info(){
    field_info* temp = (field_info*)malloc(sizeof(field_info));
    if (!temp){
        return NULL;
    }
    temp->add = add_double;
    temp->multip = multip_double;
    return temp;
}

int types_are_double(const vector* a, const vector* b){
    return (a->info == double_field_info && b->info == double_field_info);
}

int is_equal_double(const vector* a, const vector* b){
    if (!types_are_double(a,b)){return -1;}
    return (*(double*)(a->x)==*(double*)(b->x)&&*(double*)(a->y)==*(double*)(b->y));
}

vector* add_double(const vector* a, const vector* b){
    if(!types_are_double(a, b)){return NULL;}
    vector* result = (vector*)malloc(sizeof(vector));
    double* new_x = malloc(sizeof(double));
    double* new_y = malloc(sizeof(double));
    if (!result || !new_x || !new_y){
        free(new_x); free(new_y); free(result);
        return NULL;
    }
    *new_x = *(double*)(a->x) + *(double*)(b->x);
    *new_y = *(double*)(a->y) + *(double*)(b->y);
    result->x = new_x;
    result->y = new_y;
    result->info = get_double_field_info();
    return (void*)result;
}

int multip_double(const vector* a, const vector*b, void* result){
    if(!types_are_double(a, b)){return 0;}
    *(double*)result = (*(double*)(a->x))*(*(double*)(b->x)) + (*(double*)(a->y))*(*(double*)(b->y));
    return 1;
}
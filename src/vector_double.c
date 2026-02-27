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
    temp->add = add_double;
    temp->multip = multip_double;
}

vector* add_double(const vector* a, const vector* b){
    if(!types_is_equal(a, b)){return;}
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
    return (void*)result;
}

double multip_double(vector* a, vector* b){
    if(!types_is_equal(a, b)){return;}
    double result;
    result = (*(double*)(a->x))*(*(double*)(b->x)) + (*(double*)(a->y))*(*(double*)(b->y));
    return result;
}
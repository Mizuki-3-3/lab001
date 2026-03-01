#include "vector.h"

vector new_vector(void* x, void* y, int is_int){
    vector vec;
    vec.x = x;
    vec.y = y;
    if(is_int){vec.info = get_int_field_info();}
    else{vec.info = get_double_field_info();}
    return vec;
}


//for floats if it'll be needed
// static field_info* float_field_info;

// field_info* create_float_field_info(){
//     field_info* temp = (field_info*)malloc(sizeof(field_info));
//     if (!temp){
//         return;
//     }
//     temp->add = add_float;
//     temp->multip = multip_float;
//     return temp;
// }

// field_info* get_float_field_info() {
//     if (!float_field_info) {
//         float_field_info = create_int_field_info();
//     }
//     return float_field_info;
// }

// void* add_float(const vector* a, const vector* b){
//     vector* result = (vector*)malloc(sizeof(vector));
//     float* new_x = malloc(sizeof(float));
//     float* new_y = malloc(sizeof(float));
//     if (!result || !new_x || !new_y){
//         free(new_x); free(new_y); free(result);
//         return NULL;
//     }
//     *new_x = *(float*)(a->x) + *(float*)(b->x);
//     *new_y = *(float*)(a->y) + *(float*)(b->y);
//     result->x = new_x;
//     result->y = new_y;
//     return (void*)result;
// }
// float multip_float(vector a, vector b){
//     float result;
//     result = (*(float*)a.x)*(*(float*)b.x) + (*(float*)a.y)*(*(float*)b.y);
//     return result;
// }
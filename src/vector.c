#include "vector.h"

vector new_vector(void* x, void* y, int is_int){
    vector vec;
    vec.x = x;
    vec.y = y;
    if(is_int){vec.info = get_int_field_info();}
    else{vec.info = get_double_field_info();}
    return vec;
}

void del_vector(vector* v){
    free(v->x);
    free(v->y);
    free(v);
}

vector* add(const vector* vec1, const vector* vec2){
    return vec1->info->add(vec1, vec2);
}

int multip(const vector* vec1, const vector* vec2, void* res){
    return vec1->info->multip(vec1, vec2, res);
}

int equal(const vector* vec1, const vector* vec2){
    return(vec1->info->equal(vec1, vec2));
}


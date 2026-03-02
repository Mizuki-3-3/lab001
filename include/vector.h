#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
#include <stdlib.h>

typedef struct field_info field_info;

typedef struct{
    void* x;
    void* y;
    field_info* info;
}vector;

typedef struct{
    vector* (*add)(vector* vec1, vector* vec2);
    int (*multip)(vector* vec1, vector* vec2, void* res);
}field_info;

vector new_vector(void* x, void* y, int is_int);

vector* add_int(const vector* a, const vector* b);
vector* add_double(const vector* a, const vector* b);
// void* add_float(const vector* a, const vector* b);

int multip_int(const vector* a,const vector* b, void* res);
int multip_double(const vector* a,const vector* b, void* res);
// float multip_float(vector a, vector b);

field_info* get_double_field_info(void);
field_info* create_double_field_info(void);
field_info* get_int_field_info(void);
field_info* create_int_field_info(void);

int types_are_double(vector* a, vector* b);
int types_are_int(vector* a, vector* b);
int is_equal_int(vector* a, vector* b);
int is_equal_double(vector* a, vector* b);

#endif
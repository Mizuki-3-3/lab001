#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef struct field_info field_info;

typedef struct{
    void* x;
    void* y;
    field_info* info;
}vector;

struct field_info{
    vector* (*add)(const vector* vec1, const vector* vec2);
    int (*multip)(const vector* vec1, const vector* vec2, void* res);
};

vector new_vector(void* x, void* y, int is_int);
void del_vector(vector* v);

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

int types_are_double(const vector* a, const vector* b);
int types_are_int(const vector* a, const vector* b);
int is_equal_int(const vector* a, const vector* b);
int is_equal_double(const vector* a, const vector* b);

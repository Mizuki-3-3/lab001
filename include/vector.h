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
    int (*equal)(const vector* vec1, const vector* vec2);
};

vector* add(const vector* vec1, const vector* vec2);
int multip(const vector* vec1, const vector* vec2, void* res);
int equal(const vector* vec1, const vector* vec2);
int get_xi(vector* v);
int get_yi(vector* v);
double get_xd(vector* v);
double get_yd(vector*v);

vector new_vector(void* x, void* y, int is_int);
void del_vector(vector* v);

vector* add_int(const vector* a, const vector* b);
vector* add_double(const vector* a, const vector* b);

int multip_int(const vector* a,const vector* b, void* res);
int multip_double(const vector* a,const vector* b, void* res);

field_info* get_double_field_info(void);
field_info* create_double_field_info(void);
field_info* get_int_field_info(void);
field_info* create_int_field_info(void);

int types_are_double(const vector* a, const vector* b);
int types_are_int(const vector* a, const vector* b);
int equal_int(const vector* a, const vector* b);
int equal_double(const vector* a, const vector* b);

#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void* x;
    void* y;
    field_info* info;
}vector;

typedef struct{
    vector* (*add)(vector vec1, vector vec2);
    vector* (*multip)(vector vec1, vector vec2);
}field_info;

typedef struct{
    vector* next;
    vector* value;
}list_node;

typedef struct{
    list_node* head;
    list_node* tail;
    field_info* list_type;
    int size;
}list;



vector new_vector(void* x, void* y, int is_int);

vector* add_int(const vector* a, const vector* b);
vector* add_double(const vector* a, const vector* b);
// void* add_float(const vector* a, const vector* b);

int multip_int(vector* a, vector* b);
double multip_double(vector* a, vector* b);
// float multip_float(vector a, vector b);

field_info* get_double_field_info(void);
field_info* create_double_field_info(void);
field_info* get_int_field_info(void);
field_info* create_int_field_info(void);

int types_is_equal(vector* vec1, vector* vec2);
int is_equal(vector* vec1, vector* vec2);

#endif
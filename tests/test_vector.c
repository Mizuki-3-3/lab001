#include "vector.h"
#include "test.h"
#include "assertions.h"
#include <math.h>
#include <limits.h>


static int double_eq(double a, double b) {  ///проверочка на точность
    return fabs(a - b) < (1e-9);
}

TEST(create_int_vector) {
    int x = 5, y = -3;
    vector v = new_vector(&x, &y, 1);
    field_info* int_info = get_int_field_info();
    assert((v.x == &x)&&(v.y == &y)&&(v.info == int_info));
}

TEST(create_double_vector) {
    double x = 2.5, y = -1.2;
    vector v = new_vector(&x, &y, 0);
    field_info* double_info = get_double_field_info();
    assert(v.info == double_info&&v.y == &y&&v.x == &x);
}

TEST(new_int_zero) {
    int x = 0, y = 0;
    vector v = new_vector(&x, &y, 1);
    assert(v.x == &x && v.y == &y);
    assert(v.info == get_int_field_info());
}

TEST(new_double_negative) {
    double x = -1.5, y = -2.5;
    vector v = new_vector(&x, &y, 0);
    assert(v.x == &x && v.y == &y);
    assert(v.info == get_double_field_info());
}

TEST(new_double_zero){
    double x = 0.0, y = 0.0;
    vector v = new_vector(&x, &y, 1);
    assert(v.x == &x && v.y == &y);
    assert(v.info == get_int_field_info());
}
////////тесты сравнения типов
TEST(types_are_int_same) {
    int x1 = 1, y1 = 2;
    int x2 = 3, y2 = 4;
    vector v1 = new_vector(&x1, &y1, 1);
    vector v2 = new_vector(&x2, &y2, 1);
    assert(types_are_int(&v1, &v2));
}

TEST(types_are_int_different) {
    int xi = 1, yi = 2;
    double xd = 1.0, yd = 2.0;
    vector v_int = new_vector(&xi, &yi, 1);
    vector v_double = new_vector(&xd, &yd, 0);
    assert(!types_are_int(&v_int, &v_double));
}

TEST(types_are_double_same) {
    double x1 = 1.0, y1 = 2.0;
    double x2 = 3.0, y2 = 4.0;
    vector v1 = new_vector(&x1, &y1, 0);
    vector v2 = new_vector(&x2, &y2, 0);
    assert(types_are_double(&v1, &v2));
}

TEST(types_are_double_different) {
    int xi = 1, yi = 2;
    double xd = 1.0, yd = 2.0;
    vector v_int = new_vector(&xi, &yi, 1);
    vector v_double = new_vector(&xd, &yd, 0);
    assert(!types_are_double(&v_int, &v_double));
}
TEST(types_are_int_with_null_info) {
    int x = 1, y = 2;
    vector v = new_vector(&x, &y, 1);
    vector v2 = v;
    v2.info = NULL;
    assert(types_are_int(&v, &v2) == 0);
}

TEST(types_are_int_both_double) {
    double x = 1.0, y = 2.0;
    vector v = new_vector(&x, &y, 0);
    vector v2 = new_vector(&x, &y, 0);
    assert(types_are_int(&v, &v2) == 0);
}

TEST(types_are_int_same_object) {
    int x = 1, y = 2;
    vector v = new_vector(&x, &y, 1);
    assert(types_are_int(&v, &v) == 1);
}

TEST(types_are_double_with_null_info) {
    double x = 1.0, y = 2.0;
    vector v = new_vector(&x, &y, 0);
    vector v2 = v;
    v2.info = NULL;
    assert(types_are_double(&v, &v2) == 0);
}

TEST(types_are_double_both_int) {
    int x = 1, y = 2;
    vector v = new_vector(&x, &y, 1);
    vector v2 = new_vector(&x, &y, 1);
    assert(types_are_double(&v, &v2) == 0);
}

TEST(types_are_double_same_object) {
    double x = 1.0, y = 2.0;
    vector v = new_vector(&x, &y, 0);
    assert(types_are_double(&v, &v) == 1);
}

////////тест сравнение
TEST(is_equal_int_equal) {
    int x1 = 3, y1 = 4;
    int x2 = 3, y2 = 4;
    vector v1 = new_vector(&x1, &y1, 1);
    vector v2 = new_vector(&x2, &y2, 1);
    int result = is_equal_int(&v1, &v2);
    assert(result == 1);
}

TEST(is_equal_int_simmetry) {
    int x1 = 3, y1 = 4;
    vector v1 = new_vector(&x1, &y1, 1);
    int result = is_equal_int(&v1, &v1);
    assert(result == 1);
}

TEST(is_equal_int_not_equal_1) {
    int x1 = 3, y1 = 4;
    int x2 = 5, y2 = 6;
    vector v1 = new_vector(&x1, &y1, 1);
    vector v2 = new_vector(&x2, &y2, 1);
    int result = is_equal_int(&v1, &v2);
    assert(result == 0);
}

TEST(is_equal_int_not_equal_2) {
    int x1 = 3, y1 = 4;
    int x2 = 5, y2 = 6;
    vector v1 = new_vector(&x1, &y1, 1);
    vector v2 = new_vector(&x2, &y2, 1);
    int result = is_equal_int(&v2, &v1);   //ПОМЕНЯЛИ 1 И 2 МЕСТАМИ
    assert(result == 0);
}

TEST(is_equal_int_diff_y) {
    int x1 = 5, y1 = 10;
    int x2 = 5, y2 = 20;
    vector v1 = new_vector(&x1, &y1, 1);
    vector v2 = new_vector(&x2, &y2, 1);
    assert(is_equal_int(&v1, &v2) == 0);
}

TEST(is_equal_int_diff_x) {
    int x1 = 20, y1 = 10;
    int x2 = 5, y2 = 10;
    vector v1 = new_vector(&x1, &y1, 1);
    vector v2 = new_vector(&x2, &y2, 1);
    assert(is_equal_int(&v1, &v2) == 0);
}

TEST(is_equal_int_different_types) {
    int xi = 3, yi = 4;
    double xd = 3.0, yd = 4.0;
    vector v_int = new_vector(&xi, &yi, 1);
    vector v_double = new_vector(&xd, &yd, 0);
    int result = is_equal_int(&v_int, &v_double);
    assert(result == -1);
}

TEST(is_equal_double_equal) {
    double x1 = 1.5, y1 = 2.5;
    double x2 = 1.5, y2 = 2.5;
    vector v1 = new_vector(&x1, &y1, 0);
    vector v2 = new_vector(&x2, &y2, 0);
    int result = is_equal_double(&v1, &v2);
    assert(result == 1);
}

TEST(is_equal_double_not_equal) {
    double x1 = 1.5, y1 = 2.5;
    double x2 = 1.6, y2 = 2.6;
    vector v1 = new_vector(&x1, &y1, 0);
    vector v2 = new_vector(&x2, &y2, 0);
    int result = is_equal_double(&v1, &v2);
    assert(result == 0);
}

TEST(is_equal_double_different_types) {
    int xi = 1, yi = 2;
    double xd = 1.5, yd = 2.5;
    vector v_int = new_vector(&xi, &yi, 1);
    vector v_double = new_vector(&xd, &yd, 0);
    int result = is_equal_double(&v_int, &v_double);
    assert(result == -1);
}

TEST(is_equal_double_nan) {
    double nan = NAN;
    double y = 2.0;
    vector v1 = new_vector(&nan, &y, 0);
    vector v2 = new_vector(&nan, &y, 0);
    assert(is_equal_double(&v1, &v2) == 0);  
}

TEST(is_equal_double_inf) {
    double inf = INFINITY;
    double y = 2.0;
    vector v1 = new_vector(&inf, &y, 0);
    vector v2 = new_vector(&inf, &y, 0);
    assert(is_equal_double(&v1, &v2) == 1);
}

TEST(is_equal_double_neg_zero) {
    double nzero = -0.0;
    double pzero = 0.0;
    vector v1 = new_vector(&nzero, &nzero, 0);
    vector v2 = new_vector(&pzero, &pzero, 0);
    assert(is_equal_double(&v1, &v2) == 1);
}

/////////сложение тест

TEST(add_int_simple) {
    int x1 = 3, y1 = 4;
    int x2 = 1, y2 = 2;
    vector v1 = new_vector(&x1, &y1, 1);
    vector v2 = new_vector(&x2, &y2, 1);
    vector* sum = add_int(&v1, &v2);
    assert(sum != NULL&&*(int*)sum->x == 4&&*(int*)sum->y == 6);
    free(sum->x);
    free(sum->y);
    free(sum);
}

TEST(add_int_commutative) {
    int x1 = 3, y1 = 4;
    int x2 = 1, y2 = 2;
    vector v1 = new_vector(&x1, &y1, 1);
    vector v2 = new_vector(&x2, &y2, 1);
    vector* sum1 = add_int(&v1, &v2);
    vector* sum2 = add_int(&v2, &v1);
    assert((*(int*)sum1->x == *(int*)sum2->x)&&(*(int*)sum1->y == *(int*)sum2->y));
    del_vector(sum1);
    del_vector(sum2);
}

TEST(add_int_zero) {
    int x1 = 5, y1 = -7;
    int x2 = 0, y2 = 0;
    vector v1 = new_vector(&x1, &y1, 1);
    vector v2 = new_vector(&x2, &y2, 1);
    vector* sum = add_int(&v1, &v2);
    assert(sum != NULL&&*(int*)sum->x == 5&&*(int*)sum->y == -7);
    free(sum->x); free(sum->y); free(sum);
}

TEST(add_int_negative) {
    int x1 = -2, y1 = 5;
    int x2 = -3, y2 = -4;
    vector v1 = new_vector(&x1, &y1, 1);
    vector v2 = new_vector(&x2, &y2, 1);
    vector* sum = add_int(&v1, &v2);
    assert(sum != NULL&&*(int*)sum->x == -5&&*(int*)sum->y == 1);
    free(sum->x); free(sum->y); free(sum);
}

TEST(add_int_type_mismatch) {
    int xi = 3, yi = 4;
    double xd = 1.0, yd = 2.0;
    vector v_int = new_vector(&xi, &yi, 1);
    vector v_double = new_vector(&xd, &yd, 0);
    vector* sum = add_int(&v_int, &v_double);
    assert(sum == NULL);
}


TEST(add_double_simple) {
    double x1 = 1.5, y1 = 2.5;
    double x2 = 0.5, y2 = 1.5;
    vector v1 = new_vector(&x1, &y1, 0);
    vector v2 = new_vector(&x2, &y2, 0);
    vector* sum = add_double(&v1, &v2);
    assert(sum != NULL&&double_eq(*(double*)sum->x, 2.0)&&double_eq(*(double*)sum->y, 4.0));
    free(sum->x); free(sum->y); free(sum);
}

TEST(add_double_zero) {
    double x1 = 3.3, y1 = -4.4;
    double x2 = 0.0, y2 = -0.0;
    vector v1 = new_vector(&x1, &y1, 0);
    vector v2 = new_vector(&x2, &y2, 0);
    vector* sum = add_double(&v1, &v2);
    assert(sum != NULL && double_eq(*(double*)sum->x, 3.3) && double_eq(*(double*)sum->y, -4.4));
    free(sum->x); free(sum->y); free(sum);
}

TEST(add_double_negative) {
    double x1 = -1.2, y1 = 2.3;
    double x2 = -3.4, y2 = -5.6;
    vector v1 = new_vector(&x1, &y1, 0);
    vector v2 = new_vector(&x2, &y2, 0);
    vector* sum = add_double(&v1, &v2);
    assert(sum != NULL && double_eq(*(double*)sum->x, -4.6)&&double_eq(*(double*)sum->y, -3.3));
    free(sum->x); free(sum->y); free(sum);
}

TEST(add_double_precision) {
    double x1 = 1.0/3.0, y1 = 1.0/7.0;
    double x2 = 2.0/3.0, y2 = 3.0/7.0;
    vector v1 = new_vector(&x1, &y1, 0);
    vector v2 = new_vector(&x2, &y2, 0);
    vector* sum = add_double(&v1, &v2);
    assert(sum != NULL && double_eq(*(double*)sum->x, 1.0)&&double_eq(*(double*)sum->y, 4.0/7.0));
    free(sum->x); free(sum->y); free(sum);
}

TEST(add_double_type_mismatch) {
    int xi = 1, yi = 2;
    double xd = 3.0, yd = 4.0;
    vector v_int = new_vector(&xi, &yi, 1);
    vector v_double = new_vector(&xd, &yd, 0);
    vector* sum = add_double(&v_int, &v_double);
    assert(sum == NULL);
}

TEST(add_double_nan) {
    double nan = NAN;
    double x1 = 1.5, y1 = 2.5;
    vector v1 = new_vector(&x1, &y1, 0);
    vector v2 = new_vector(&nan, &y1, 0);
    vector* sum = add_double(&v1, &v2);
    assert(sum != NULL);
    del_vector(sum);
}

TEST(add_double_small_not_null) {
    double x1 = 1e-200, y1 = 1e-200;
    double x2 = 2e-200, y2 = 3e-200;
    vector v1 = new_vector(&x1, &y1, 0);
    vector v2 = new_vector(&x2, &y2, 0);
    vector* sum = add_double(&v1, &v2);
    assert(sum != NULL);
    del_vector(sum);
}

//////////////тесты умножение

TEST(multip_int_simple) {
    int x1 = 2, y1 = 3;
    int x2 = 4, y2 = 5;
    vector v1 = new_vector(&x1, &y1, 1);
    vector v2 = new_vector(&x2, &y2, 1);
    int result;
    int err = multip_int(&v1, &v2, &result);
    assert(err == 1&&result == 23);
}

TEST(multip_int_commutativity) {
    int x1 = 2, y1 = 3;
    int x2 = 4, y2 = 5;
    vector v1 = new_vector(&x1, &y1, 1);
    vector v2 = new_vector(&x2, &y2, 1);
    int result1, result2;
    int err = multip_int(&v1, &v2, &result1)&&multip_int(&v2, &v1, &result2);
    assert(err == 1&&(result1 == result2));
}

TEST(multip_int_zero) {
    int x1 = 2, y1 = 3;
    int x2 = 0, y2 = 0;
    vector v1 = new_vector(&x1, &y1, 1);
    vector v2 = new_vector(&x2, &y2, 1);
    int result;
    int err = multip_int(&v1, &v2, &result);
    assert(err == 1 && result == 0);
}

TEST(multip_int_1_vector) {
    int x1 = 2, y1 = 3;
    int x2 = 1, y2 = 1;
    vector v1 = new_vector(&x1, &y1, 1);
    vector v2 = new_vector(&x2, &y2, 1);
    int result;
    int err = multip_int(&v1, &v2, &result);
    assert(err == 1 && result == 5);
}
TEST(multip_int_negative) {
    int x1 = -2, y1 = 3;
    int x2 = 4, y2 = -5;
    vector v1 = new_vector(&x1, &y1, 1);
    vector v2 = new_vector(&x2, &y2, 1);
    int result;
    int err = multip_int(&v1, &v2, &result);
    assert(err == 1&&result == -23);
}

TEST(multip_int_type_mismatch) {
    int xi = 1, yi = 2;
    double xd = 3.0, yd = 4.0;
    vector v_int = new_vector(&xi, &yi, 1);
    vector v_double = new_vector(&xd, &yd, 0);
    int result;
    int err = multip_int(&v_int, &v_double, &result);
    assert(err == 0);
}

TEST(multip_int_large_result) {
    int x1 = 10000, y1 = 20000;
    int x2 = 30000, y2 = 40000;
    vector v1 = new_vector(&x1, &y1, 1);
    vector v2 = new_vector(&x2, &y2, 1);
    int result;
    int err = multip_int(&v1, &v2, &result);
    assert((result == 10000*30000 + 20000*40000)&&err==1);
}
///произведение даблов

TEST(multip_double_simple) {
    double x1 = 1.5, y1 = 2.0;
    double x2 = 3.0, y2 = 4.0;
    vector v1 = new_vector(&x1, &y1, 0);
    vector v2 = new_vector(&x2, &y2, 0);
    double result;
    int err = multip_double(&v1, &v2, &result);
    assert(err == 1);
    assert(double_eq(result, 12.5));
}

TEST(multip_double_commutativity) {
    double x1 = 1.5, y1 = 2.0;
    double x2 = 4.5, y2 = -6.5;
    vector v1 = new_vector(&x1, &y1, 0);
    vector v2 = new_vector(&x2, &y2, 0);
    double result1, result2;
    int no_err = multip_double(&v1, &v2, &result1)&&multip_double(&v2, &v1, &result2);
    assert(no_err&&(result1==result2));
}

TEST(multip_double_zero) {
    double x1 = 1.5, y1 = 2.0;
    double x2 = 0.0, y2 = 0.0;
    vector v1 = new_vector(&x1, &y1, 0);
    vector v2 = new_vector(&x2, &y2, 0);
    double result;
    int no_err = multip_double(&v1, &v2, &result);
    assert(no_err&&(result==0.0));
}

TEST(multip_double_1_vector) {
    double x1 = 1.5, y1 = 2.0;
    double x2 = 1.0, y2 = 1.0;
    vector v1 = new_vector(&x1, &y1, 0);
    vector v2 = new_vector(&x2, &y2, 0);
    double result;
    int no_err = multip_double(&v1, &v2, &result);
    assert(no_err&&(result==3.5));
}

TEST(multip_double_negative) {
    double x1 = -1.5, y1 = 2.0;
    double x2 = 3.0, y2 = -4.0;
    vector v1 = new_vector(&x1, &y1, 0);
    vector v2 = new_vector(&x2, &y2, 0);
    double result;
    int err = multip_double(&v1, &v2, &result);
    assert(err == 1&&double_eq(result, -12.5));
}

TEST(multip_double_precision) {
    double x1 = 1.0/3.0, y1 = 1.0/7.0;
    double x2 = 2.0/3.0, y2 = 3.0/7.0;
    vector v1 = new_vector(&x1, &y1, 0);
    vector v2 = new_vector(&x2, &y2, 0);
    double result;
    int err = multip_double(&v1, &v2, &result);//// (1/3)*(2/3) + (1/7)*(3/7) =0.283446
    double expected = 2.0/9.0 + 3.0/49.0;
    assert(err&&double_eq(result, expected));
}

TEST(multip_double_type_mismatch) {
    int xi = 1, yi = 2;
    double xd = 3.0, yd = 4.0;
    vector v_int = new_vector(&xi, &yi, 1);
    vector v_double = new_vector(&xd, &yd, 0);
    double result;
    int err = multip_double(&v_int, &v_double, &result);
    assert(!err);
}

TEST(multip_double_inf_err) {
    double inf = INFINITY;
    double x1 = 1.5, y1 = 2.5;
    double y2 = 4.0;
    vector v1 = new_vector(&x1, &y1, 0);
    vector v2 = new_vector(&inf, &y2, 0);
    double result;
    int no_err = multip_double(&v1, &v2, &result);
    assert(no_err && isinf(result));
}

TEST(multip_double_nan_err) {
    double nan = NAN;
    double x1 = 1.5, y1 = 2.5;
    vector v1 = new_vector(&x1, &y1, 0);
    vector v2 = new_vector(&nan, &y1, 0);
    double result;
    int err = multip_double(&v1, &v2, &result);
    assert(!err);
}

TEST(multip_double_huge_err) {
    double x1 = 1e200, y1 = 0;
    double x2 = 1e200, y2 = 0;
    vector v1 = new_vector(&x1, &y1, 0);
    vector v2 = new_vector(&x2, &y2, 0);
    double result;
    int err = multip_double(&v1, &v2, &result);
    assert(err && isinf(result));
}

TEST(get_int_field_info_not_null) {
    field_info* info = get_int_field_info();
    assert(info != NULL);
}

TEST(get_int_field_info_singleton) {
    field_info* info1 = get_int_field_info();
    field_info* info2 = get_int_field_info();
    assert(info1 == info2);
}

TEST(get_int_field_info_add_not_null) {
    field_info* info = get_int_field_info();
    assert(info->add != NULL);
}

TEST(get_int_field_info_multip_not_null) {
    field_info* info = get_int_field_info();
    assert(info->multip != NULL);
}

TEST(get_double_field_info_not_null) {
    field_info* info = get_double_field_info();
    assert(info != NULL);
}

TEST(get_double_field_info_singleton) {
    field_info* info1 = get_double_field_info();
    field_info* info2 = get_double_field_info();
    assert(info1 == info2);
}

TEST(get_double_field_info_add_not_null) {
    field_info* info = get_double_field_info();
    assert(info->add != NULL);
}

TEST(get_double_field_info_multip_not_null) {
    field_info* info = get_double_field_info();
    assert(info->multip != NULL);
}
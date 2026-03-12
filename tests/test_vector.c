#include "vector.h"
#include "test.h"
#include "assertions.h"
#include <math.h>

static int double_eq(double a, double b) {  ///проверочка на точность
    return fabs(a - b) < (1e-9);
}

void test_create_int_vector() {
    int x = 5, y = -3;
    vector v = new_vector(&x, &y, 1);
    assert(v.x == &x);
    assert(v.y == &y);
    field_info* int_info = get_int_field_info();
    assert(v.info == int_info);
}

void test_create_double_vector() {
    double x = 2.5, y = -1.2;
    vector v = new_vector(&x, &y, 0);
    field_info* double_info = get_double_field_info();
    assert(v.info == double_info&&v.y == &y&&v.x == &x);
}

void test_new_int_zero() {
    int x = 0, y = 0;
    vector v = new_vector(&x, &y, 1);
    assert(v.x == &x && v.y == &y);
    assert(v.info == get_int_field_info());
}

void test_new_double_negative() {
    double x = -1.5, y = -2.5;
    vector v = new_vector(&x, &y, 0);
    assert(v.x == &x && v.y == &y);
    assert(v.info == get_double_field_info());
}

void test_new_int_large() {
    int x = INT_MAX, y = INT_MIN;
    vector v = new_vector(&x, &y, 1);
    assert(v.x == &x && v.y == &y);
    assert(v.info == get_int_field_info());
}
////////тесты сравнения типов
void test_types_are_int_same() {
    int x1 = 1, y1 = 2;
    int x2 = 3, y2 = 4;
    vector v1 = new_vector(&x1, &y1, 1);
    vector v2 = new_vector(&x2, &y2, 1);
    assert(types_are_int(&v1, &v2));
}

void test_types_are_int_different() {
    int xi = 1, yi = 2;
    double xd = 1.0, yd = 2.0;
    vector v_int = new_vector(&xi, &yi, 1);
    vector v_double = new_vector(&xd, &yd, 0);
    assert(!types_are_int(&v_int, &v_double));
}

void test_types_are_double_same() {
    double x1 = 1.0, y1 = 2.0;
    double x2 = 3.0, y2 = 4.0;
    vector v1 = new_vector(&x1, &y1, 0);
    vector v2 = new_vector(&x2, &y2, 0);
    assert(types_are_double(&v1, &v2));
}

void test_types_are_double_different() {
    int xi = 1, yi = 2;
    double xd = 1.0, yd = 2.0;
    vector v_int = new_vector(&xi, &yi, 1);
    vector v_double = new_vector(&xd, &yd, 0);
    assert(!types_are_double(&v_int, &v_double));
}
void test_types_are_int_with_null_info() {
    int x = 1, y = 2;
    vector v = new_vector(&x, &y, 1);
    vector v2 = v;
    v2.info = NULL;   // искусственно портим
    assert(types_are_int(&v, &v2) == 0);
}

void test_types_are_int_both_double() {
    double x = 1.0, y = 2.0;
    vector v = new_vector(&x, &y, 0);
    vector v2 = new_vector(&x, &y, 0);
    assert(types_are_int(&v, &v2) == 0);
}

void test_types_are_int_same_object() {
    int x = 1, y = 2;
    vector v = new_vector(&x, &y, 1);
    assert(types_are_int(&v, &v) == 1);
}

void test_types_are_double_with_null_info() {
    double x = 1.0, y = 2.0;
    vector v = new_vector(&x, &y, 0);
    vector v2 = v;
    v2.info = NULL;
    assert(types_are_double(&v, &v2) == 0);
}

void test_types_are_double_both_int() {
    int x = 1, y = 2;
    vector v = new_vector(&x, &y, 1);
    vector v2 = new_vector(&x, &y, 1);
    assert(types_are_double(&v, &v2) == 0);
}

void test_types_are_double_same_object() {
    double x = 1.0, y = 2.0;
    vector v = new_vector(&x, &y, 0);
    assert(types_are_double(&v, &v) == 1);
}

////////тест сравнение
void test_is_equal_int_equal() {
    int x1 = 3, y1 = 4;
    int x2 = 3, y2 = 4;
    vector v1 = new_vector(&x1, &y1, 1);
    vector v2 = new_vector(&x2, &y2, 1);
    int result = is_equal_int(&v1, &v2);
    assert(result == 1);
}

void test_is_equal_int_not_equal() {
    int x1 = 3, y1 = 4;
    int x2 = 5, y2 = 6;
    vector v1 = new_vector(&x1, &y1, 1);
    vector v2 = new_vector(&x2, &y2, 1);
    int result = is_equal_int(&v1, &v2);
    assert(result == 0);
}

void test_is_equal_int_max_values() {
    int x1 = INT_MAX, y1 = INT_MIN;
    int x2 = INT_MAX, y2 = INT_MIN;
    vector v1 = new_vector(&x1, &y1, 1);
    vector v2 = new_vector(&x2, &y2, 1);
    assert(is_equal_int(&v1, &v2) == 1);
}

void test_is_equal_int_diff_y() {
    int x1 = 5, y1 = 10;
    int x2 = 5, y2 = 20;
    vector v1 = new_vector(&x1, &y1, 1);
    vector v2 = new_vector(&x2, &y2, 1);
    assert(is_equal_int(&v1, &v2) == 0);
}

void test_is_equal_int_same_pointer() {
    int x = 5, y = 10;
    vector v = new_vector(&x, &y, 1);
    assert(is_equal_int(&v, &v) == 1);
}

void test_is_equal_int_different_types() {
    int xi = 3, yi = 4;
    double xd = 3.0, yd = 4.0;
    vector v_int = new_vector(&xi, &yi, 1);
    vector v_double = new_vector(&xd, &yd, 0);
    int result = is_equal_int(&v_int, &v_double);
    assert(result == -1);
}

void test_is_equal_double_equal() {
    double x1 = 1.5, y1 = 2.5;
    double x2 = 1.5, y2 = 2.5;
    vector v1 = new_vector(&x1, &y1, 0);
    vector v2 = new_vector(&x2, &y2, 0);
    int result = is_equal_double(&v1, &v2);
    assert(result == 1);
}

void test_is_equal_double_not_equal() {
    double x1 = 1.5, y1 = 2.5;
    double x2 = 1.6, y2 = 2.6;
    vector v1 = new_vector(&x1, &y1, 0);
    vector v2 = new_vector(&x2, &y2, 0);
    int result = is_equal_double(&v1, &v2);
    assert(result == 0);
}

void test_is_equal_double_different_types() {
    int xi = 1, yi = 2;
    double xd = 1.5, yd = 2.5;
    vector v_int = new_vector(&xi, &yi, 1);
    vector v_double = new_vector(&xd, &yd, 0);
    int result = is_equal_double(&v_int, &v_double);
    assert(result == -1);
}

void test_is_equal_double_nan() {
    double nan = NAN;
    double y = 2.0;
    vector v1 = new_vector(&nan, &y, 0);
    vector v2 = new_vector(&nan, &y, 0);
    assert(is_equal_double(&v1, &v2) == 0);  
}

void test_is_equal_double_inf() {
    double inf = INFINITY;
    double y = 2.0;
    vector v1 = new_vector(&inf, &y, 0);
    vector v2 = new_vector(&inf, &y, 0);
    assert(is_equal_double(&v1, &v2) == 1);
}

void test_is_equal_double_neg_zero() {
    double nzero = -0.0;
    double pzero = 0.0;
    vector v1 = new_vector(&nzero, &nzero, 0);
    vector v2 = new_vector(&pzero, &pzero, 0);
    assert(is_equal_double(&v1, &v2) == 1);
}

/////////сложение тест

void test_add_int_simple() {
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

void test_add_int_zero() {
    int x1 = 5, y1 = -7;
    int x2 = 0, y2 = 0;
    vector v1 = new_vector(&x1, &y1, 1);
    vector v2 = new_vector(&x2, &y2, 1);
    vector* sum = add_int(&v1, &v2);
    assert(sum != NULL&&*(int*)sum->x == 5&&*(int*)sum->y == -7);
    free(sum->x); free(sum->y); free(sum);
}

void test_add_int_negative() {
    int x1 = -2, y1 = 5;
    int x2 = -3, y2 = -4;
    vector v1 = new_vector(&x1, &y1, 1);
    vector v2 = new_vector(&x2, &y2, 1);
    vector* sum = add_int(&v1, &v2);
    assert(sum != NULL&&*(int*)sum->x == -5&&*(int*)sum->y == 1);
    free(sum->x); free(sum->y); free(sum);
}

void test_add_int_large() {
    int x1 = 1000000, y1 = 2000000;
    int x2 = 3000000, y2 = 4000000;
    vector v1 = new_vector(&x1, &y1, 1);
    vector v2 = new_vector(&x2, &y2, 1);
    vector* sum = add_int(&v1, &v2);
    assert(sum != NULL&&*(int*)sum->x == 4000000&&*(int*)sum->y == 6000000);
    free(sum->x); free(sum->y); free(sum);
}

void test_add_int_type_mismatch() {
    int xi = 3, yi = 4;
    double xd = 1.0, yd = 2.0;
    vector v_int = new_vector(&xi, &yi, 1);
    vector v_double = new_vector(&xd, &yd, 0);
    vector* sum = add_int(&v_int, &v_double);
    assert(sum == NULL);
}

void test_add_int_positive_negative_not_null() {
    int x1 = 10, y1 = -5;
    int x2 = -3, y2 = 7;
    vector v1 = new_vector(&x1, &y1, 1);
    vector v2 = new_vector(&x2, &y2, 1);
    vector* sum = add_int(&v1, &v2);
    assert(sum != NULL);
    free(sum->x); free(sum->y); free(sum);
}

void test_add_double_simple() {
    double x1 = 1.5, y1 = 2.5;
    double x2 = 0.5, y2 = 1.5;
    vector v1 = new_vector(&x1, &y1, 0);
    vector v2 = new_vector(&x2, &y2, 0);
    vector* sum = add_double(&v1, &v2);
    assert(sum != NULL&&double_eq(*(double*)sum->x, 2.0)&&double_eq(*(double*)sum->y, 4.0));
    free(sum->x); free(sum->y); free(sum);
}

void test_add_double_zero() {
    double x1 = 3.3, y1 = -4.4;
    double x2 = 0.0, y2 = 0.0;
    vector v1 = new_vector(&x1, &y1, 0);
    vector v2 = new_vector(&x2, &y2, 0);
    vector* sum = add_double(&v1, &v2);
    assert(sum != NULL && double_eq(*(double*)sum->x, 3.3) && double_eq(*(double*)sum->y, -4.4));
    free(sum->x); free(sum->y); free(sum);
}

void test_add_double_negative() {
    double x1 = -1.2, y1 = 2.3;
    double x2 = -3.4, y2 = -5.6;
    vector v1 = new_vector(&x1, &y1, 0);
    vector v2 = new_vector(&x2, &y2, 0);
    vector* sum = add_double(&v1, &v2);
    assert(sum != NULL && double_eq(*(double*)sum->x, -4.6)&&double_eq(*(double*)sum->y, -3.3));
    free(sum->x); free(sum->y); free(sum);
}

void test_add_double_precision() {
    double x1 = 1.0/3.0, y1 = 1.0/7.0;
    double x2 = 2.0/3.0, y2 = 3.0/7.0;
    vector v1 = new_vector(&x1, &y1, 0);
    vector v2 = new_vector(&x2, &y2, 0);
    vector* sum = add_double(&v1, &v2);
    assert(sum != NULL && double_eq(*(double*)sum->x, 1.0)&&double_eq(*(double*)sum->y, 4.0/7.0));
    free(sum->x); free(sum->y); free(sum);
}

void test_add_double_type_mismatch() {
    int xi = 1, yi = 2;
    double xd = 3.0, yd = 4.0;
    vector v_int = new_vector(&xi, &yi, 1);
    vector v_double = new_vector(&xd, &yd, 0);
    vector* sum = add_double(&v_int, &v_double);
    assert(sum == NULL);
}

void test_add_double_nan_not_null() {
    double nan = NAN;
    double x1 = 1.5, y1 = 2.5;
    vector v1 = new_vector(&x1, &y1, 0);
    vector v2 = new_vector(&nan, &y1, 0);
    vector* sum = add_double(&v1, &v2);
    assert(sum != NULL);
    free(sum->x); free(sum->y); free(sum);
}

void test_add_double_small_not_null() {
    double x1 = 1e-200, y1 = 1e-200;
    double x2 = 2e-200, y2 = 3e-200;
    vector v1 = new_vector(&x1, &y1, 0);
    vector v2 = new_vector(&x2, &y2, 0);
    vector* sum = add_double(&v1, &v2);
    assert(sum != NULL);
    free(sum->x); free(sum->y); free(sum);
}

//////////////тесты умножение

void test_multip_int_simple() {
    int x1 = 2, y1 = 3;
    int x2 = 4, y2 = 5;
    vector v1 = new_vector(&x1, &y1, 1);
    vector v2 = new_vector(&x2, &y2, 1);
    int result;
    int err = multip_int(&v1, &v2, &result);
    assert(err == 1&&result == 23);
}

void test_multip_int_zero() {
    int x1 = 2, y1 = 3;
    int x2 = 0, y2 = 0;
    vector v1 = new_vector(&x1, &y1, 1);
    vector v2 = new_vector(&x2, &y2, 1);
    int result;
    int err = multip_int(&v1, &v2, &result);
    assert(err == 1&&result == 0);
}

void test_multip_int_negative() {
    int x1 = -2, y1 = 3;
    int x2 = 4, y2 = -5;
    vector v1 = new_vector(&x1, &y1, 1);
    vector v2 = new_vector(&x2, &y2, 1);
    int result;
    int err = multip_int(&v1, &v2, &result);
    assert(err == 1&&result == -23);
}

void test_multip_int_zero_vector() {
    int x1 = 0, y1 = 0;
    int x2 = 7, y2 = 8;
    vector v1 = new_vector(&x1, &y1, 1);
    vector v2 = new_vector(&x2, &y2, 1);
    int result;
    int err = multip_int(&v1, &v2, &result);
    assert(err == 1&&result == 0);
}

void test_multip_int_type_mismatch() {
    int xi = 1, yi = 2;
    double xd = 3.0, yd = 4.0;
    vector v_int = new_vector(&xi, &yi, 1);
    vector v_double = new_vector(&xd, &yd, 0);
    int result;
    int err = multip_int(&v_int, &v_double, &result);
    assert(err == 0);
}

void test_multip_int_large_result() {
    int x1 = 10000, y1 = 20000;
    int x2 = 30000, y2 = 40000;
    vector v1 = new_vector(&x1, &y1, 1);
    vector v2 = new_vector(&x2, &y2, 1);
    int result;
    int err = multip_int(&v1, &v2, &result);
    assert((result == 10000*30000 + 20000*40000)&&err==1);
}
///произведение даблов

void test_multip_double_simple() {
    double x1 = 1.5, y1 = 2.0;
    double x2 = 3.0, y2 = 4.0;
    vector v1 = new_vector(&x1, &y1, 0);
    vector v2 = new_vector(&x2, &y2, 0);
    double result;
    int err = multip_double(&v1, &v2, &result);
    assert(err == 1);
    assert(double_eq(result, 12.5));
}

void test_multip_double_zero() {
    double x1 = 1.5, y1 = 2.0;
    double x2 = 0.0, y2 = 0.0;
    vector v1 = new_vector(&x1, &y1, 0);
    vector v2 = new_vector(&x2, &y2, 0);
    double result;
    int err = multip_double(&v1, &v2, &result);
    assert(err == 1&&double_eq(result, 0.0));
}

void test_multip_double_negative() {
    double x1 = -1.5, y1 = 2.0;
    double x2 = 3.0, y2 = -4.0;
    vector v1 = new_vector(&x1, &y1, 0);
    vector v2 = new_vector(&x2, &y2, 0);
    double result;
    int err = multip_double(&v1, &v2, &result);
    assert(err == 1&&double_eq(result, -12.5));
}

void test_multip_double_precision() {
    double x1 = 1.0/3.0, y1 = 1.0/7.0;
    double x2 = 2.0/3.0, y2 = 3.0/7.0;
    vector v1 = new_vector(&x1, &y1, 0);
    vector v2 = new_vector(&x2, &y2, 0);
    double result;
    int err = multip_double(&v1, &v2, &result);
    // (1/3)*(2/3) + (1/7)*(3/7) =0.283446
    double expected = 2.0/9.0 + 3.0/49.0;
    assert(err == 1&&double_eq(result, expected));
}

void test_multip_double_type_mismatch() {
    int xi = 1, yi = 2;
    double xd = 3.0, yd = 4.0;
    vector v_int = new_vector(&xi, &yi, 1);
    vector v_double = new_vector(&xd, &yd, 0);
    double result;
    int err = multip_double(&v_int, &v_double, &result);
    assert(err == 0);
}

void test_multip_double_inf_err() {
    double inf = INFINITY;
    double x1 = 1.5, y1 = 2.5;
    double y2 = 4.0;
    vector v1 = new_vector(&x1, &y1, 0);
    vector v2 = new_vector(&inf, &y2, 0);
    double result;
    int err = multip_double(&v1, &v2, &result);
    assert(err == 1 && isinf(result));
}

void test_multip_double_nan_err() {
    double nan = NAN;
    double x1 = 1.5, y1 = 2.5;
    vector v1 = new_vector(&x1, &y1, 0);
    vector v2 = new_vector(&nan, &y1, 0);
    double result;
    int err = multip_double(&v1, &v2, &result);
    assert(err == 1 && isnan(result));
}

void test_multip_double_huge_err() {
    double x1 = 1e200, y1 = 0;
    double x2 = 1e200, y2 = 0;
    vector v1 = new_vector(&x1, &y1, 0);
    vector v2 = new_vector(&x2, &y2, 0);
    double result;
    int err = multip_double(&v1, &v2, &result);
    assert(err == 1 && isinf(result));
}

void test_get_int_field_info_not_null() {
    field_info* info = get_int_field_info();
    assert(info != NULL);
}

void test_get_int_field_info_singleton() {
    field_info* info1 = get_int_field_info();
    field_info* info2 = get_int_field_info();
    assert(info1 == info2);
}

void test_get_int_field_info_add_not_null() {
    field_info* info = get_int_field_info();
    assert(info->add != NULL);
}

void test_get_int_field_info_multip_not_null() {
    field_info* info = get_int_field_info();
    assert(info->multip != NULL);
}

void test_get_double_field_info_not_null() {
    field_info* info = get_double_field_info();
    assert(info != NULL);
}

void test_get_double_field_info_singleton() {
    field_info* info1 = get_double_field_info();
    field_info* info2 = get_double_field_info();
    assert(info1 == info2);
}

void test_get_double_field_info_add_not_null() {
    field_info* info = get_double_field_info();
    assert(info->add != NULL);
}

void test_get_double_field_info_multip_not_null() {
    field_info* info = get_double_field_info();
    assert(info->multip != NULL);
}

void init_vector_tests(void) {
    register_test("test_create_int_vector", test_create_int_vector);
    register_test("test_create_double_vector", test_create_double_vector);
    register_test("test_types_are_int_same", test_types_are_int_same);
    register_test("test_types_are_int_different", test_types_are_int_different);
    register_test("test_types_are_double_same", test_types_are_double_same);
    register_test("test_types_are_double_different", test_types_are_double_different);
    register_test("test_is_equal_int_equal", test_is_equal_int_equal);
    register_test("test_is_equal_int_not_equal", test_is_equal_int_not_equal);
    register_test("test_is_equal_int_different_types", test_is_equal_int_different_types);
    register_test("test_is_equal_double_equal", test_is_equal_double_equal);
    register_test("test_is_equal_double_not_equal", test_is_equal_double_not_equal);
    register_test("test_is_equal_double_different_types", test_is_equal_double_different_types);
    register_test("test_add_int_simple", test_add_int_simple);
    register_test("test_add_int_zero", test_add_int_zero);
    register_test("test_add_int_negative", test_add_int_negative);
    register_test("test_add_int_large", test_add_int_large);
    register_test("test_add_int_type_mismatch", test_add_int_type_mismatch);
    register_test("test_add_double_simple", test_add_double_simple);
    register_test("test_add_double_zero", test_add_double_zero);
    register_test("test_add_double_negative", test_add_double_negative);
    register_test("test_add_double_precision", test_add_double_precision);
    register_test("test_add_double_type_mismatch", test_add_double_type_mismatch);
    register_test("test_multip_int_simple", test_multip_int_simple);
    register_test("test_multip_int_zero", test_multip_int_zero);
    register_test("test_multip_int_negative", test_multip_int_negative);
    register_test("test_multip_int_zero_vector", test_multip_int_zero_vector);
    register_test("test_multip_int_type_mismatch", test_multip_int_type_mismatch);
    register_test("test_multip_double_simple", test_multip_double_simple);
    register_test("test_multip_double_zero", test_multip_double_zero);
    register_test("test_multip_double_negative", test_multip_double_negative);
    register_test("test_multip_double_precision", test_multip_double_precision);
    register_test("test_multip_double_type_mismatch", test_multip_double_type_mismatch);
    register_test("test_new_int_zero", test_new_int_zero);
    register_test("test_new_double_negative", test_new_double_negative);
    register_test("test_new_int_large", test_new_int_large);
    register_test("test_types_are_int_with_null_info", test_types_are_int_with_null_info);
    register_test("test_types_are_int_both_double", test_types_are_int_both_double);
    register_test("test_types_are_int_same_object", test_types_are_int_same_object);
    register_test("test_types_are_double_with_null_info", test_types_are_double_with_null_info);
    register_test("test_types_are_double_both_int", test_types_are_double_both_int);
    register_test("test_types_are_double_same_object", test_types_are_double_same_object);
    register_test("test_is_equal_int_max_values", test_is_equal_int_max_values);
    register_test("test_is_equal_int_diff_y", test_is_equal_int_diff_y);
    register_test("test_is_equal_int_same_pointer", test_is_equal_int_same_pointer);
    register_test("test_is_equal_double_nan", test_is_equal_double_nan);
    register_test("test_is_equal_double_inf", test_is_equal_double_inf);
    register_test("test_is_equal_double_neg_zero", test_is_equal_double_neg_zero);
    register_test("test_add_int_positive_negative_not_null", test_add_int_positive_negative_not_null);
    register_test("test_add_double_nan_not_null", test_add_double_nan_not_null);
    register_test("test_add_double_small_not_null", test_add_double_small_not_null);
    register_test("test_multip_int_large_result", test_multip_int_large_result);
    register_test("test_multip_double_inf_err", test_multip_double_inf_err);
    register_test("test_multip_double_nan_err", test_multip_double_nan_err);
    register_test("test_multip_double_huge_err", test_multip_double_huge_err);
    register_test("test_get_int_field_info_not_null", test_get_int_field_info_not_null);
    register_test("test_get_int_field_info_singleton", test_get_int_field_info_singleton);
    register_test("test_get_int_field_info_add_not_null", test_get_int_field_info_add_not_null);
    register_test("test_get_int_field_info_multip_not_null", test_get_int_field_info_multip_not_null);
    register_test("test_get_double_field_info_not_null", test_get_double_field_info_not_null);
    register_test("test_get_double_field_info_singleton", test_get_double_field_info_singleton);
    register_test("test_get_double_field_info_add_not_null", test_get_double_field_info_add_not_null);
    register_test("test_get_double_field_info_multip_not_null", test_get_double_field_info_multip_not_null);
}
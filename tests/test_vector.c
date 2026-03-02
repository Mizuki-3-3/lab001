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

////////тест сравнение
void test_is_equal_int_equal() {
    int x1 = 3, y1 = 4;
    int x2 = 3, y2 = 4;
    vector v1 = new_vector(&x1, &y1, 1);
    vector v2 = new_vector(&x2, &y2, 1);
    int result = is_equal_int(&v1, &v2);
    assert(result == 0);
}

void test_is_equal_int_not_equal() {
    int x1 = 3, y1 = 4;
    int x2 = 5, y2 = 6;
    vector v1 = new_vector(&x1, &y1, 1);
    vector v2 = new_vector(&x2, &y2, 1);
    int result = is_equal_int(&v1, &v2);
    assert(result == 0);
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
}
#include "vector.h"
#include "test.h"
#include "assertions.h"
#include <math.h>
#include <limits.h>

////////тесты сравнения типов
TEST(types_are_int_same) {
    int x1 = 1, y1 = 2;
    int x2 = 3, y2 = 4;
    vector v1 = new_vector(&x1, &y1, 1);
    vector v2 = new_vector(&x2, &y2, 1);
    assert(types_are_int(&v1, &v2));
}

TEST(types_are_int_same_object) {
    int x = 1, y = 2;
    vector v = new_vector(&x, &y, 1);
    assert(types_are_int(&v, &v));
}

TEST(types_are_int_different) {
    int xi = 1, yi = 2;
    double xd = 1.0, yd = 2.0;
    vector v_int = new_vector(&xi, &yi, 1);
    vector v_double = new_vector(&xd, &yd, 0);
    assert(!types_are_int(&v_int, &v_double));
}

TEST(types_are_int_with_null_info) {
    int x = 1, y = 2;
    vector v = new_vector(&x, &y, 1);
    vector v2 = v;
    v2.info = NULL;
    assert(!types_are_int(&v, &v2));
}

TEST(types_are_int_both_double) {
    double x = 1.0, y = 2.0;
    vector v = new_vector(&x, &y, 0);
    vector v2 = new_vector(&x, &y, 0);
    assert(!types_are_int(&v, &v2));
}

TEST(types_are_double_same) {
    double x1 = 1.0, y1 = 2.0;
    double x2 = 3.0, y2 = 4.0;
    vector v1 = new_vector(&x1, &y1, 0);
    vector v2 = new_vector(&x2, &y2, 0);
    assert(types_are_double(&v1, &v2));
}

TEST(types_are_double_same_object) {
    double x = 1.0, y = 2.0;
    vector v = new_vector(&x, &y, 0);
    assert(types_are_double(&v, &v));
}

TEST(types_are_double_different) {
    int xi = 1, yi = 2;
    double xd = 1.0, yd = 2.0;
    vector v_int = new_vector(&xi, &yi, 1);
    vector v_double = new_vector(&xd, &yd, 0);
    assert(!types_are_double(&v_int, &v_double));
}

TEST(types_are_double_with_null_info) {
    double x = 1.0, y = 2.0;
    vector v = new_vector(&x, &y, 0);
    vector v2 = v;
    v2.info = NULL;
    assert(!types_are_double(&v, &v2));
}

TEST(types_are_double_both_int) {
    int x = 1, y = 2;
    vector v = new_vector(&x, &y, 1);
    vector v2 = new_vector(&x, &y, 1);
    assert(!types_are_double(&v, &v2));
}


////////тест сравнение
TEST(is_equal_int_equal) {
    int x1 = 3, y1 = -4;
    int x2 = 3, y2 = -4;
    vector v1 = new_vector(&x1, &y1, 1);
    vector v2 = new_vector(&x2, &y2, 1);
    assert(equal(&v1, &v2));
}

TEST(is_equal_int_equal_symmetry) {
    int x1 = 3, y1 = -4;
    int x2 = 3, y2 = -4;
    vector v1 = new_vector(&x1, &y1, 1);
    vector v2 = new_vector(&x2, &y2, 1);
    assert(equal(&v1, &v2)&&equal(&v2, &v1)); //ПОМЕНЯЛИ 1 И 2 МЕСТАМИ
}

TEST(is_equal_int_reflexivity) {
    int x1 = 3, y1 = 4;
    vector v1 = new_vector(&x1, &y1, 1);
    assert(equal(&v1, &v1));
}

TEST(is_equal_int_not_equal_1) {
    int x1 = 3, y1 = 4;
    int x2 = 5, y2 = 6;
    vector v1 = new_vector(&x1, &y1, 1);
    vector v2 = new_vector(&x2, &y2, 1);
    assert(!equal(&v1, &v2));
}

TEST(is_equal_int_not_equal_2) {
    int x1 = 3, y1 = 4;
    int x2 = 5, y2 = 6;
    vector v1 = new_vector(&x1, &y1, 1);
    vector v2 = new_vector(&x2, &y2, 1); 
    assert(!equal(&v2, &v1)); //ПОМЕНЯЛИ 1 И 2 МЕСТАМИ
}

TEST(is_equal_int_diff_y) {
    int x1 = 5, y1 = 10;
    int x2 = 5, y2 = 20;
    vector v1 = new_vector(&x1, &y1, 1);
    vector v2 = new_vector(&x2, &y2, 1);
    assert(!equal(&v1, &v2));
}

TEST(is_equal_int_diff_x) {
    int x1 = 20, y1 = 10;
    int x2 = 5, y2 = 10;
    vector v1 = new_vector(&x1, &y1, 1);
    vector v2 = new_vector(&x2, &y2, 1);
    assert(!equal(&v1, &v2));
}

TEST(is_equal_int_different_types) {
    int xi = 3, yi = 4;
    double xd = 3.0, yd = 4.0;
    vector v_int = new_vector(&xi, &yi, 1);
    vector v_double = new_vector(&xd, &yd, 0);
    assert(equal(&v_int, &v_double) == -1);
}

TEST(is_equal_double_equal) {
    double x1 = 1.5, y1 = 2.5;
    double x2 = 1.5, y2 = 2.5;
    vector v1 = new_vector(&x1, &y1, 0);
    vector v2 = new_vector(&x2, &y2, 0);
    assert(equal(&v1, &v2));
}

TEST(is_equal_double_equal_symmetry) {
    double x1 = 1.5, y1 = 2.5;
    double x2 = 1.5, y2 = 2.5;
    vector v1 = new_vector(&x1, &y1, 1);
    vector v2 = new_vector(&x2, &y2, 1);
    assert(equal(&v1, &v2)&&equal(&v2, &v1)); //ПОМЕНЯЛИ 1 И 2 МЕСТАМИ
}

TEST(is_equal_double_reflexivity) {
    double x1 = 1.5, y1 = 2.5;
    vector v1 = new_vector(&x1, &y1, 1);
    assert(equal(&v1, &v1));
}

TEST(is_equal_double_not_equal) {
    double x1 = 1.5, y1 = 2.5;
    double x2 = 1.6, y2 = 2.6;
    vector v1 = new_vector(&x1, &y1, 0);
    vector v2 = new_vector(&x2, &y2, 0);
    assert(!equal(&v1, &v2));
}

TEST(is_equal_double_different_types) {
    int xi = 1, yi = 2;
    double xd = 1.5, yd = 2.5;
    vector v_int = new_vector(&xi, &yi, 1);
    vector v_double = new_vector(&xd, &yd, 0);
    int result = equal(&v_int, &v_double);
    assert(result == -1);
}

TEST(is_equal_double_nan) {
    double nan = NAN;
    double y = 2.0;
    vector v1 = new_vector(&nan, &y, 0);
    vector v2 = new_vector(&nan, &y, 0);
    assert(!equal(&v1, &v2));  
}

TEST(is_equal_double_inf) {
    double inf = INFINITY;
    double y = 2.0;
    vector v1 = new_vector(&inf, &y, 0);
    vector v2 = new_vector(&inf, &y, 0);
    assert(equal(&v1, &v2));
}

TEST(is_equal_double_neg_zero) {
    double nzero = -0.0;
    double pzero = 0.0;
    vector v1 = new_vector(&nzero, &nzero, 0);
    vector v2 = new_vector(&pzero, &pzero, 0);
    assert(equal(&v1, &v2));
}

/////////сложение тест

TEST(add_int_simple) {
    int x1 = 3, y1 = 4;
    int x2 = 1, y2 = 2;
    int xe = 4, ye = 6;
    vector v1 = new_vector(&x1, &y1, 1);
    vector v2 = new_vector(&x2, &y2, 1);
    vector expected = new_vector(&xe, &ye, 1);
    vector* sum = add(&v1, &v2);
    assert(equal(sum, &expected));
    del_vector(sum);
}

TEST(add_int_commutative) {
    int x1 = 3, y1 = 4;
    int x2 = 1, y2 = 2;
    vector v1 = new_vector(&x1, &y1, 1);
    vector v2 = new_vector(&x2, &y2, 1);
    vector* sum1 = add(&v1, &v2);
    vector* sum2 = add(&v2, &v1);
    assert(equal(sum1, sum2));
    del_vector(sum1);
    del_vector(sum2);
}

TEST(add_int_zero) {
    int x1 = 5, y1 = -7;
    int x2 = 0, y2 = 0;
    vector v1 = new_vector(&x1, &y1, 1);
    vector v2 = new_vector(&x2, &y2, 1);
    vector* sum = add(&v1, &v2);
    assert(equal(&v1, sum));
    del_vector(sum);
}

TEST(add_int_negative) {
    int x1 = -2, y1 = 5;
    int x2 = -3, y2 = -4;
    int xe = -5, ye = 1;
    vector v1 = new_vector(&x1, &y1, 1);
    vector v2 = new_vector(&x2, &y2, 1);
    vector expected = new_vector(&xe, &ye, 1);
    vector* sum = add(&v1, &v2);
    assert(equal(sum, &expected));
    del_vector(sum);
}

TEST(add_int_type_mismatch) {
    int xi = 3, yi = 4;
    double xd = 1.0, yd = 2.0;
    vector v_int = new_vector(&xi, &yi, 1);
    vector v_double = new_vector(&xd, &yd, 0);
    vector* sum = add(&v_int, &v_double);
    assert(sum == NULL);
}

TEST(add_int_opposite_elem){
    int x1 = 4, y1 = 7;
    int x2 = -4, y2 = -7;
    int xz = 0, yz = 0;
    vector v1 = new_vector(&x1, &y1, 1);
    vector v2 = new_vector(&x2, &y2, 1);
    vector zero = new_vector(&xz, &yz, 1);
    vector* sum = add(&v1, &v2);
    assert(equal(&zero, sum));
    del_vector(sum);
}

TEST(add_double_simple) {
    double x1 = 1.5, y1 = 2.5;
    double x2 = 7.2, y2 = 1.6;
    double xe = 8.7, ye = 4.1;
    vector v1 = new_vector(&x1, &y1, 0);
    vector v2 = new_vector(&x2, &y2, 0);
    vector expected = new_vector(&xe, &ye, 0);
    vector* sum = add(&v1, &v2);
    assert(equal(sum, &expected));
    del_vector(sum);
}

TEST(add_double_zero) {
    double x1 = 3.3, y1 = -4.4;
    double x2 = 0.0, y2 = -0.0;
    vector v1 = new_vector(&x1, &y1, 0);
    vector v2 = new_vector(&x2, &y2, 0);
    vector* sum = add(&v1, &v2);
    assert(equal(&v1, sum));
    del_vector(sum);
}

TEST(add_double_negative) {
    double x1 = -1.2, y1 = -2.3;
    double x2 = -3.4, y2 = -5.6;
    double xe = -4.6, ye = (-2.3-5.6);
    vector v1 = new_vector(&x1, &y1, 0);
    vector v2 = new_vector(&x2, &y2, 0);
    vector expected = new_vector(&xe, &ye, 0);
    vector* sum = add(&v1, &v2);
    assert(equal(sum, &expected));
    del_vector(sum);
}

TEST(add_double_opposite_elem){
    double x1 = 4.98427, y1 = 7.49825;
    double x2 = -4.98427, y2 = -7.49825;
    double xe = -0, ye = 0;
    vector v1 = new_vector(&x1, &y1, 0);
    vector v2 = new_vector(&x2, &y2, 0);
    vector expected = new_vector(&xe, &ye, 0);
    vector* sum = add(&v1, &v2);
    assert(equal(sum, &expected));
    del_vector(sum);
}

TEST(add_double_precision) {
    double x1 = 1.0/3.0, y1 = 1.0/7.0;
    double x2 = 2.0/3.0, y2 = 3.0/7.0;
    double xe = 1.0/3.0 + 2.0/3.0, ye = 1.0/7.0 + 3.0/7.0;
    vector v1 = new_vector(&x1, &y1, 0);
    vector v2 = new_vector(&x2, &y2, 0);
    vector expected = new_vector(&xe, &ye, 0);
    vector* sum = add(&v1, &v2);
    assert(equal(sum, &expected));
    del_vector(sum);
}

TEST(add_double_type_mismatch) {
    int xi = 1, yi = 2;
    double xd = 3.0, yd = 4.0;
    vector v_int = new_vector(&xi, &yi, 1);
    vector v_double = new_vector(&xd, &yd, 0);
    vector* sum = add(&v_int, &v_double);
    assert(sum == NULL);
}

TEST(add_double_nan) {
    double nan = NAN;
    double x1 = 1.5, y1 = 2.5;
    vector v1 = new_vector(&x1, &y1, 0);
    vector v2 = new_vector(&nan, &y1, 0);
    vector* sum = add(&v1, &v2);
    assert(sum != NULL);
    del_vector(sum);
}

TEST(add_double_small_not_null) {
    double x1 = 1e-200, y1 = 1e-200;
    double x2 = 2e-200, y2 = 3e-200;
    vector v1 = new_vector(&x1, &y1, 0);
    vector v2 = new_vector(&x2, &y2, 0);
    vector* sum = add(&v1, &v2);
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
    int err = multip(&v1, &v2, &result);
    assert(err == 1);
    assert(result == 23);
}

TEST(multip_int_commutativity) {
    int x1 = 2, y1 = 3;
    int x2 = 4, y2 = 5;
    vector v1 = new_vector(&x1, &y1, 1);
    vector v2 = new_vector(&x2, &y2, 1);
    int result1, result2;
    int err = multip(&v1, &v2, &result1)&&multip(&v2, &v1, &result2);
    assert(err);
    assert(result1 == result2);
}

TEST(multip_int_zero) {
    int x1 = 2, y1 = 3;
    int x2 = 0, y2 = 0;
    vector v1 = new_vector(&x1, &y1, 1);
    vector v2 = new_vector(&x2, &y2, 1);
    int result;
    int err = multip(&v1, &v2, &result);
    assert(err);
    assert(result == 0);
}

TEST(multip_int_1_vector) {
    int x1 = 2, y1 = 3;
    int x2 = 1, y2 = 1;
    vector v1 = new_vector(&x1, &y1, 1);
    vector v2 = new_vector(&x2, &y2, 1);
    int result;
    int err = multip(&v1, &v2, &result);
    assert(err);
    assert(result == 5);
}

TEST(multip_int_negative) {
    int x1 = -2, y1 = 3;
    int x2 = 4, y2 = -5;
    vector v1 = new_vector(&x1, &y1, 1);
    vector v2 = new_vector(&x2, &y2, 1);
    int result;
    int err = multip(&v1, &v2, &result);
    assert(err);
    assert(result == -23);
}

TEST(multip_int_type_mismatch) {
    int xi = 1, yi = 2;
    double xd = 3.0, yd = 4.0;
    vector v_int = new_vector(&xi, &yi, 1);
    vector v_double = new_vector(&xd, &yd, 0);
    int result;
    int err = multip(&v_int, &v_double, &result);
    assert(!err);
}

TEST(multip_int_large_result) {
    int x1 = 10000, y1 = 20000;
    int x2 = 30000, y2 = 40000;
    vector v1 = new_vector(&x1, &y1, 1);
    vector v2 = new_vector(&x2, &y2, 1);
    int result;
    int err = multip(&v1, &v2, &result);
    assert(result == 10000*30000 + 20000*40000);
    assert(err);
}
///произведение даблов

TEST(multip_double_simple) {
    double x1 = 1.5, y1 = 2.0;
    double x2 = 3.0, y2 = 4.0;
    vector v1 = new_vector(&x1, &y1, 0);
    vector v2 = new_vector(&x2, &y2, 0);
    double result;
    int err = multip(&v1, &v2, &result);
    assert(err);
    assert(double_eq(result, 12.5));
}

TEST(multip_double_commutativity) {
    double x1 = 1.5, y1 = 2.0;
    double x2 = 4.5, y2 = -6.5;
    vector v1 = new_vector(&x1, &y1, 0);
    vector v2 = new_vector(&x2, &y2, 0);
    double result1, result2;
    int err = multip(&v1, &v2, &result1)&&multip(&v2, &v1, &result2);
    assert(err);
    assert(result1==result2);
}

TEST(multip_double_zero) {
    double x1 = 1.5, y1 = 2.0;
    double x2 = 0.0, y2 = 0.0;
    vector v1 = new_vector(&x1, &y1, 0);
    vector v2 = new_vector(&x2, &y2, 0);
    double result;
    int err = multip(&v1, &v2, &result);
    assert(err);
    assert(result==0.0);
}

TEST(multip_double_1_vector) {
    double x1 = 1.5, y1 = 2.0;
    double x2 = 1.0, y2 = 1.0;
    vector v1 = new_vector(&x1, &y1, 0);
    vector v2 = new_vector(&x2, &y2, 0);
    double result;
    int err = multip(&v1, &v2, &result);
    assert(err);
    assert(result==3.5);
}

TEST(multip_double_negative) {
    double x1 = -1.5, y1 = 2.0;
    double x2 = 3.0, y2 = -4.0;
    vector v1 = new_vector(&x1, &y1, 0);
    vector v2 = new_vector(&x2, &y2, 0);
    double result;
    int err = multip(&v1, &v2, &result);
    assert(err);
    assert(double_eq(result, -12.5));
}

TEST(multip_double_precision) {
    double x1 = 1.0/3.0, y1 = 1.0/7.0;
    double x2 = 2.0/3.0, y2 = 3.0/7.0;
    vector v1 = new_vector(&x1, &y1, 0);
    vector v2 = new_vector(&x2, &y2, 0);
    double result;
    int err = multip(&v1, &v2, &result);
    double expected = 2.0/9.0 + 3.0/49.0;
    assert(err);
    assert(double_eq(result, expected));
}

TEST(multip_double_type_mismatch) {
    int xi = 1, yi = 2;
    double xd = 3.0, yd = 4.0;
    vector v_int = new_vector(&xi, &yi, 1);
    vector v_double = new_vector(&xd, &yd, 0);
    double result;
    int err = multip(&v_int, &v_double, &result);
    assert(!err);
}

TEST(multip_double_inf_err) {
    double inf = INFINITY;
    double x1 = 1.5, y1 = 2.5;
    double y2 = 4.0;
    vector v1 = new_vector(&x1, &y1, 0);
    vector v2 = new_vector(&inf, &y2, 0);
    double result;
    int err = multip(&v1, &v2, &result);
    assert(err);
    assert(isinf(result));
}

TEST(multip_double_nan_err) {
    double nan = NAN;
    double x1 = 1.5, y1 = 2.5;
    vector v1 = new_vector(&x1, &y1, 0);
    vector v2 = new_vector(&nan, &y1, 0);
    double result;
    int err = multip(&v1, &v2, &result);
    assert(err);
    assert(isnan(result));
}

TEST(multip_double_huge_err) {
    double x1 = 1e200, y1 = 0;
    double x2 = 1e200, y2 = 0;
    vector v1 = new_vector(&x1, &y1, 0);
    vector v2 = new_vector(&x2, &y2, 0);
    double result;
    int err = multip(&v1, &v2, &result);
    assert(err);
    assert(isinf(result));
}
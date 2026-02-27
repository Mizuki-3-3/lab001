#include <stdio.h>

#define assert(expr) \
    ((!!(expr)) \
    ? assert_secces (#expr, __FILE__, __LINE__) \
    : assert_fail (#expr, __FILE__, __LINE__))
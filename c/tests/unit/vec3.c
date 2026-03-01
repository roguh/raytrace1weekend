#include "../../lib/vec3.h"
#include <math.h>
#include <stdio.h>
#include <assert.h>

#define EPSILON 1e-9
#define ASSERT_DOUBLE_EQ(expected, actual) \
    assert(fabs((expected) - (actual)) < EPSILON)

#define ASSERT_VEC3_EQ(expected, actual) \
    do { \
        ASSERT_DOUBLE_EQ((expected).e[0], (actual).e[0]); \
        ASSERT_DOUBLE_EQ((expected).e[1], (actual).e[1]); \
        ASSERT_DOUBLE_EQ((expected).e[2], (actual).e[2]); \
    } while(0)

void test_construction() {
    printf("Testing construction...\n");

    vec3 zero = vec0();
    ASSERT_VEC3_EQ(((vec3){{0, 0, 0}}), zero);

    vec3 constant = vecc(5.0);
    ASSERT_VEC3_EQ(((vec3){{5.0, 5.0, 5.0}}), constant);

    vec3 manual = (vec3){{1.0, 2.0, 3.0}};
    ASSERT_DOUBLE_EQ(1.0, manual.e[0]);
    ASSERT_DOUBLE_EQ(2.0, manual.e[1]);
    ASSERT_DOUBLE_EQ(3.0, manual.e[2]);
}

void test_accessors() {
    printf("Testing accessors...\n");

    vec3 v = (vec3){{1.5, 2.5, 3.5}};

    ASSERT_DOUBLE_EQ(1.5, vec_x(v));
    ASSERT_DOUBLE_EQ(2.5, vec_y(v));
    ASSERT_DOUBLE_EQ(3.5, vec_z(v));

    ASSERT_DOUBLE_EQ(1.5, at(v, 0));
    ASSERT_DOUBLE_EQ(2.5, at(v, 1));
    ASSERT_DOUBLE_EQ(3.5, at(v, 2));
}

void test_negation() {
    printf("Testing negation...\n");

    vec3 v = (vec3){{1.0, -2.0, 3.0}};
    vec3 negated = neg(v);

    ASSERT_VEC3_EQ(((vec3){{-1.0, 2.0, -3.0}}), negated);
}

void test_addition() {
    printf("Testing addition...\n");

    vec3 a = (vec3){{1.0, 2.0, 3.0}};
    vec3 b = (vec3){{4.0, 5.0, 6.0}};

    vec3 result = add(a, b);
    ASSERT_VEC3_EQ(((vec3){{5.0, 7.0, 9.0}}), result);

    // Test addAssign
    vec3 c = a;
    addAssign(&c, &b);
    ASSERT_VEC3_EQ(result, c);
}

void test_subtraction() {
    printf("Testing subtraction...\n");

    vec3 a = (vec3){{5.0, 7.0, 9.0}};
    vec3 b = (vec3){{1.0, 2.0, 3.0}};

    vec3 result = sub(a, b);
    ASSERT_VEC3_EQ(((vec3){{4.0, 5.0, 6.0}}), result);
}

void test_scalar_multiplication() {
    printf("Testing scalar multiplication...\n");

    vec3 v = (vec3){{1.0, 2.0, 3.0}};
    double scalar = 2.5;

    vec3 result = mulc(v, scalar);
    ASSERT_VEC3_EQ(((vec3){{2.5, 5.0, 7.5}}), result);

    // Test in-place version
    vec3 v2 = v;
    mulC(&v2, scalar);
    ASSERT_VEC3_EQ(result, v2);
}

void test_scalar_division() {
    printf("Testing scalar division...\n");

    vec3 v = (vec3){{2.0, 4.0, 6.0}};
    double divisor = 2.0;

    vec3 result = divc(v, divisor);
    ASSERT_VEC3_EQ(((vec3){{1.0, 2.0, 3.0}}), result);

    // Test in-place version
    vec3 v2 = v;
    divC(&v2, divisor);
    ASSERT_VEC3_EQ(result, v2);
}

void test_element_wise_multiplication() {
    printf("Testing element-wise multiplication...\n");

    vec3 a = (vec3){{2.0, 3.0, 4.0}};
    vec3 b = (vec3){{1.0, 2.0, 3.0}};

    vec3 result = mul(a, b);
    ASSERT_VEC3_EQ(((vec3){{2.0, 6.0, 12.0}}), result);
}

void test_dot_product() {
    printf("Testing dot product...\n");

    vec3 a = (vec3){{1.0, 2.0, 3.0}};
    vec3 b = (vec3){{4.0, 5.0, 6.0}};

    double result = dot(a, b);
    ASSERT_DOUBLE_EQ(32.0, result); // 1*4 + 2*5 + 3*6 = 4 + 10 + 18 = 32

    // Test orthogonal vectors
    vec3 i = (vec3){{1.0, 0.0, 0.0}};
    vec3 j = (vec3){{0.0, 1.0, 0.0}};
    ASSERT_DOUBLE_EQ(0.0, dot(i, j));
}

void test_cross_product() {
    printf("Testing cross product...\n");

    vec3 i = (vec3){{1.0, 0.0, 0.0}};
    vec3 j = (vec3){{0.0, 1.0, 0.0}};

    vec3 result = cross(i, j);
    ASSERT_VEC3_EQ(((vec3){{0.0, 0.0, 1.0}}), result); // i × j = k

    vec3 result2 = cross(j, i);
    ASSERT_VEC3_EQ(((vec3){{0.0, 0.0, -1.0}}), result2); // j × i = -k

    // Test with general vectors
    vec3 a = (vec3){{1.0, 2.0, 3.0}};
    vec3 b = (vec3){{4.0, 5.0, 6.0}};
    vec3 cross_result = cross(a, b);

    // Cross product should be orthogonal to both inputs
    ASSERT_DOUBLE_EQ(0.0, dot(cross_result, a));
    ASSERT_DOUBLE_EQ(0.0, dot(cross_result, b));
}

void test_length() {
    printf("Testing length...\n");

    vec3 v = (vec3){{3.0, 4.0, 0.0}}; // 3-4-5 triangle
    ASSERT_DOUBLE_EQ(25.0, length_squared(v));
    ASSERT_DOUBLE_EQ(5.0, length(v));

    vec3 unit_vec = (vec3){{1.0, 0.0, 0.0}};
    ASSERT_DOUBLE_EQ(1.0, length(unit_vec));
    ASSERT_DOUBLE_EQ(1.0, length_squared(unit_vec));

    vec3 zero = vec0();
    ASSERT_DOUBLE_EQ(0.0, length(zero));
    ASSERT_DOUBLE_EQ(0.0, length_squared(zero));
}

void test_unit_vector() {
    printf("Testing unit vector...\n");

    vec3 v = (vec3){{3.0, 4.0, 0.0}};
    vec3 normalized = unit(v);

    ASSERT_DOUBLE_EQ(1.0, length(normalized));
    ASSERT_VEC3_EQ(((vec3){{0.6, 0.8, 0.0}}), normalized);

    // Test already unit vector
    vec3 already_unit = (vec3){{1.0, 0.0, 0.0}};
    vec3 still_unit = unit(already_unit);
    ASSERT_VEC3_EQ(already_unit, still_unit);
}

void test_zero_edge_cases() {
    printf("Testing zero vector edge cases...\n");

    vec3 zero = vec0();
    vec3 nonzero = (vec3){{1.0, 2.0, 3.0}};

    // Adding zero should not change vector
    vec3 result = add(nonzero, zero);
    ASSERT_VEC3_EQ(nonzero, result);

    // Multiplying by zero should give zero
    vec3 zero_result = mulc(nonzero, 0.0);
    ASSERT_VEC3_EQ(zero, zero_result);

    // Dot product with zero should be zero
    ASSERT_DOUBLE_EQ(0.0, dot(nonzero, zero));

    // Cross product with zero should be zero
    vec3 cross_zero = cross(nonzero, zero);
    ASSERT_VEC3_EQ(zero, cross_zero);
}

int main() {
    printf("Running vec3 unit tests...\n\n");

    test_construction();
    test_accessors();
    test_negation();
    test_addition();
    test_subtraction();
    test_scalar_multiplication();
    test_scalar_division();
    test_element_wise_multiplication();
    test_dot_product();
    test_cross_product();
    test_length();
    test_unit_vector();
    test_zero_edge_cases();

    printf("\n🎉 All tests passed! ✓\n");
    return 0;
}

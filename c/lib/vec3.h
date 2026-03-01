#ifndef VEC3_H
#define VEC3_H

#include <stdio.h>
#include <stddef.h>

typedef struct {
    double e[3];
} vec3;

typedef vec3 point3;

// Construction
vec3 vec0(void);
vec3 vecc(double c);

// Access
double vec_x(vec3 v);
double vec_y(vec3 v);
double vec_z(vec3 v);
double at(vec3 v, size_t i);

// Unary operations
vec3 neg(vec3 v);

// Mutating operations (modify in place)
vec3* addAssign(vec3* u, const vec3* v);
vec3* mulC(vec3* u, double c);
vec3* divC(vec3* u, double c);

// Non-mutating operations (return new vector)
vec3 add(const vec3 u, const vec3 v);
vec3 sub(const vec3 u, const vec3 v);
vec3 mul(const vec3 u, const vec3 v);
vec3 mulc(const vec3 u, double c);
vec3 divc(const vec3 u, double c);

// Vector operations
double dot(const vec3 u, const vec3 v);
vec3 cross(const vec3 u, const vec3 v);
double length_squared(vec3 v);
double length(vec3 v);
vec3 unit(const vec3 v);

// I/O
void fprint_vec3(FILE* out, vec3* v);
void print(vec3* v);

#endif // VEC3_H
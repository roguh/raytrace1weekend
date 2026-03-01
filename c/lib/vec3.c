#include <math.h>
#include <stddef.h>
#include <stdio.h>

typedef struct {
    // Single-precision floats would also work in case of memory contraints
    double e[3];
} vec3;

// Useful for geometric clarity
typedef vec3 point3;

vec3 vec0() {
    return (vec3){{0, 0, 0}};
}

vec3 vecc(double c) {
    return (vec3){{c, c, c}};
}

double vec_x(vec3 v) { return v.e[0]; }
double vec_y(vec3 v) { return v.e[1]; }
double vec_z(vec3 v) { return v.e[2]; }

vec3 neg(vec3 v) {
    return (vec3){{-v.e[0], -v.e[1], -v.e[2]}};
}

double at(vec3 v, size_t i) {
    return v.e[i];
}

vec3* addAssign(vec3* u, const vec3* v) {
    u->e[0] += v->e[0];
    u->e[1] += v->e[1];
    u->e[2] += v->e[2];
    return u;
}

vec3* mulC(vec3* u, double c) {
    u->e[0] *= c;
    u->e[1] *= c;
    u->e[2] *= c;
    return u;
}

vec3* divC(vec3* u, double c) {
    return mulC(u, 1 / c);
}

vec3 mulc(const vec3 u, double c) {
    return (vec3){{u.e[0] * c, u.e[1] * c, u.e[2] * c}};
}

vec3 divc(const vec3 u, double c) {
    return mulc(u, 1 / c);
}

double length_squared(vec3 v) {
   return v.e[0] * v.e[0] + v.e[1] * v.e[1] + v.e[2] * v.e[2];
}

double length(vec3 v) {
    return sqrt(length_squared(v));
}

void fprint_vec3(FILE* out, vec3* v) {
    fprintf(out, "%lf %lf %lf", v->e[0], v->e[1], v->e[2]);
}

void print(vec3* v) {
    fprint_vec3(stdout, v);
}

vec3 add(const vec3 u, const vec3 v) {
    return (vec3){{u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]}};
}

vec3 sub(const vec3 u, const vec3 v) {
    return (vec3){{u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]}};
}

vec3 mul(const vec3 u, const vec3 v) {
    return (vec3){{u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]}};
}

double dot(const vec3 u, const vec3 v) {
    return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

vec3 cross(const vec3 u, const vec3 v) {
    return (vec3){{
        u.e[1] * v.e[2] - u.e[2] * v.e[1],
        u.e[2] * v.e[0] - u.e[0] * v.e[2],
        u.e[0] * v.e[1] - u.e[1] * v.e[0],
    }};
}

vec3 unit(const vec3 v) {
    return divc(v, length(v));
}

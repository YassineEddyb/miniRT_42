#ifndef MINIRT_H
# define MINIRT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <mlx.h>
#include <stdbool.h> /* Needed for boolean datatype */

# define WIDTH 800
# define HEIGHT 600

#define RAY_T_MIN 0.0001f
#define RAY_T_MAX 1.0e30f
#define min(a,b) (((a) < (b)) ? (a) : (b))

typedef struct 
{
    float t;
    void *object;
} intesection;

typedef struct {
    int rows;
    int cols;
    float **m;
} matrix;

/* Colour definition */
typedef struct{
        float red, green, blue;
} colour;

/* The vector structure */
typedef struct {
      float x,y,z, w;
} vector;

/* The sphere */
typedef struct {
    vector pos;
    vector transform;
    float  radius;
    float diameter;
    colour rgb;
    int material;
} sphere; 

/* The ray */
typedef struct {
    vector start;
    vector dir;
} ray;

// camera
typedef struct {
    vector pos;
    vector normal;
    float fov;
} camera;

typedef struct{
    float ratio;
    colour rgb;
} ambient;

/* Light definition */
typedef struct{
    vector pos;
    colour rgb;
    float ratio;
} light;

/* Material definition */
typedef struct{
    colour diffuse;
    float reflection;
} material; 

// plane
typedef struct {
    vector pos;
    vector normal;
    float fov;
} plane;

// cylinder
typedef struct {
    vector pos;
    vector normal;
    float diameter;
    float height;
    colour rgb;
} cy;

typedef vector point;

// vector functions
vector vectorSub(vector v1, vector v2);
float vectorDot(vector v1, vector v2);
vector vectorScale(vector v, float t);
vector vectorAdd(vector v1, vector v2);
vector normalize(vector v);
vector vectorInit(float x, float y, float z, float w);

// matrix functions
matrix matrixCreate(int rows, int cols);
float determinant(matrix m);
matrix submatrix(matrix m, int row, int col);
float minor(matrix m, int rwo, int col);
float cofactor(float det, int row, int col);
float det(float **m);
float matrixDeterminant(matrix m);
void print_matrix(matrix m);
matrix matrixMult(matrix m1, matrix m2);
matrix matrixTranspose(matrix m);
matrix matrixInverse(matrix m);

// matrix transformatons
vector translate(vector v, vector translator);\
vector scale(vector v, vector scaler);
vector rotate_x(vector v, float r);
vector rotate_y(vector v, float r);
vector rotate_z(vector v, float r);

// ray functions
vector position(ray r, float t);
ray transform(ray r, vector v, char t);

// sphere functions
float *sphereIntersection(ray r, sphere s);

#endif
#ifndef MINIRT_H
# define MINIRT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <mlx.h>
#include <stdbool.h> /* Needed for boolean datatype */

# define WIDTH 300
# define HEIGHT 300

#define RAY_T_MIN 0.0001f
#define RAY_T_MAX 1.0e30f
#define min(a,b) (((a) < (b)) ? (a) : (b))

/* The vector structure */
typedef struct {
      float x,y,z, w;
} vector;

/* Colour definition */
typedef struct{
    float red, green, blue;
} colour;

/* Material definition */
typedef struct{
    colour color;
    float ambient;
    float diffuse;
    float specular;
    float shininess;
} material; 

typedef struct {
    char type;
    vector transform;
} trans;

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

/* The sphere */
typedef struct {
    vector pos;
    matrix transform;
    float  radius;
    float diameter;
    colour rgb;
    material material;
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
    colour intensity;
    float ratio;
} light;

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
} cylinder;

typedef struct s_world {
    light light;
    sphere *s;
} t_world;

typedef struct s_intersect {
    void *object;
    char type;
    float t;
} t_intersect;

typedef struct s_comps {
    float t;
    void *object;
    char type;
    vector point;
    vector eyev;
    vector normalv;
    int inside;
} t_comps;

typedef vector point;

// vector functions
vector vectorSub(vector v1, vector v2);
float vectorDot(vector v1, vector v2);
vector vectorScale(vector v, float t);
vector vectorAdd(vector v1, vector v2);
vector normalize(vector v);
vector vectorInit(float x, float y, float z, float w);
vector vectorCross(vector a, vector b);

// matrix functions
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
vector translate(vector v, vector translator, int type);
vector scale(vector v, vector scaler, int type);
vector rotate_x(vector v, float r);
vector rotate_y(vector v, float r);
vector rotate_z(vector v, float r);
vector vector_mult_matrix (vector v, matrix m, int type);

// matrix inits
matrix matrixCreate(int rows, int cols);
matrix get_matrix(vector v, char type);
matrix get_rotation_matrix(float r, int type);

// ray functions
vector position(ray r, float t);
ray transform(ray r, matrix m, int type);

// sphere functions
sphere shpereInit();
float sphereIntersection(ray r, sphere s);
vector normal_at(sphere s, vector p);
vector reflect(vector in, vector normal);

// colour functions
colour colourInit(float r, float g, float b);

// light functions
light lightInit(vector pos, colour intensity);
colour lightning(material m, light l, vector pos, vector v, vector n);

// material functions
material materials();

// world functions
t_world worldInit(light l);
t_intersect intersect_world(t_world world , ray r);
t_comps prepare_computations (ray r, t_intersect i);
colour shade_hit(t_world world, t_comps comps);
colour color_at(t_world world, ray r);

// camera functions
matrix view_transform(vector from, vector to, vector up);

#endif
#ifndef MINIRT_H
# define MINIRT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <mlx.h>
#include <stdbool.h> /* Needed for boolean datatype */

# define WIDTH 500
# define HEIGHT 300

#define RAY_T_MIN 0.0001f
#define RAY_T_MAX 1.0e30f
#define min(a,b) (((a) < (b)) ? (a) : (b))

/* The vector structure */
typedef struct {
      double x,y,z, w;
} vector;

/* Colour definition */
typedef struct{
    double red, green, blue;
} colour;

/* Material definition */
typedef struct{
    colour color;
    double ambient;
    double diffuse;
    double specular;
    double shininess;
} material; 

typedef struct {
    char type;
    vector transform;
} trans;

typedef struct 
{
    double t;
    void *object;
} intesection;

typedef struct {
    int rows;
    int cols;
    double **m;
} matrix;

/* The sphere */
typedef struct {
    vector pos;
    matrix transform;
    double  radius;
    double diameter;
    colour rgb;
    material material;
} sphere; 

/* The ray */
typedef struct {
    vector start;
    vector dir;
} ray;

// camera
typedef struct s_camera{
    vector pos;
    vector normal;
    double fov;
    matrix transform;
    double hsize;
    double vsize;
    double half_width;
    double half_height;
    double pixel_size;
} t_camera;

typedef struct{
    double ratio;
    colour rgb;
} ambient;

/* Light definition */
typedef struct{
    vector pos;
    colour intensity;
    double ratio;
} light;

// plane
typedef struct {
    vector pos;
    vector normal;
    double fov;
} plane;

// cylinder
typedef struct {
    vector pos;
    vector normal;
    double diameter;
    double height;
    colour rgb;
} cylinder;

typedef struct s_world {
    light light;
    sphere *s;
} t_world;

typedef struct s_intersect {
    void *object;
    char type;
    double t;
} t_intersect;

typedef struct s_comps {
    double t;
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
double vectorDot(vector v1, vector v2);
vector vectorScale(vector v, double t);
vector vectorAdd(vector v1, vector v2);
vector normalize(vector v);
vector vectorInit(double x, double y, double z, double w);
vector vectorCross(vector a, vector b);
double magnitude(vector v);

// matrix functions
double determinant(matrix m);
matrix submatrix(matrix m, int row, int col);
double minor(matrix m, int rwo, int col);
double cofactor(double det, int row, int col);
double det(double **m);
double matrixDeterminant(matrix m);
void print_matrix(matrix m);
matrix matrixMult(matrix m1, matrix m2);
matrix matrixTranspose(matrix m);
matrix matrixInverse(matrix m);

// matrix transformatons
vector translate(vector v, vector translator, int type);
vector scale(vector v, vector scaler, int type);
vector rotate_x(vector v, double r);
vector rotate_y(vector v, double r);
vector rotate_z(vector v, double r);
vector vector_mult_matrix (vector v, matrix m, int type);

// matrix inits
matrix matrixCreate(int rows, int cols);
matrix get_matrix(vector v, char type);
matrix get_rotation_matrix(double r, int type);

// ray functions
vector position(ray r, double t);
ray transform(ray r, matrix m, int type);
ray ray_for_pixel(t_camera camera, int x, int y);

// sphere functions
sphere shpereInit();
double sphereIntersection(ray r, sphere s);
vector normal_at(sphere s, vector p);
vector reflect(vector in, vector normal);

// colour functions
colour colourInit(double r, double g, double b);

// light functions
light lightInit(vector pos, colour intensity);
colour lightning(material m, light l, vector pos, vector v, vector n, int in_shadow);

// material functions
material materials();

// world functions
t_world worldInit(light l);
t_intersect intersect_world(t_world world , ray r);
t_comps prepare_computations (ray r, t_intersect i);
colour shade_hit(t_world world, t_comps comps);
colour color_at(t_world world, ray r);

// camera functions
t_camera cameraInit(double hsize, double wsize, double fov);
matrix view_transform(vector from, vector to, vector up);

// shadows functions
int is_shadowed(t_world world, vector point);

#endif
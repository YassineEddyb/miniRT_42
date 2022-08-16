#ifndef MINIRT_H
# define MINIRT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <float.h>
#include <mlx.h>
#include <pthread.h>
#include "Includes/parser.h"

# define WIDTH 400
# define HEIGHT 350

#define EPSILON 0.0000001f
#define RAY_T_MIN 0.0001f
#define RAY_T_MAX 1.0e30f
#define min(a,b) (((a) < (b)) ? (a) : (b))

// mlx data
 typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

/* The vector structure */
// typedef struct {
//       double x,y,z, w;
// } vector;

/* Colour definition */
// typedef struct{
//     double red, green, blue;
// } colour;

/* Material definition */
// typedef struct{
//     colour color;
//     double ambient;
//     double diffuse;
//     double specular;
//     double shininess;
// } material; 

typedef struct {
    char type;
    t_vector transform;
} trans;

typedef struct 
{
    double t;
    void *object;
} intesection;

// typedef struct {
//     int rows;
//     int cols;
//     double **m;
// } matrix;

/* The sphere */
// typedef struct {
//     vector pos;
    
//     double diameter;
//     colour rgb;
//     material material;
// } sphere; 

/* The ray */
typedef struct {
    t_vector start;
    t_vector dir;
} ray;

// camera
// typedef struct s_camera{
//     vector pos;
//     vector normal;
//     double fov;
//     matrix transform;
//     double hsize;
//     double vsize;
//     double half_width;
//     double half_height;
//     double pixel_size;
// } t_camera;

// typedef struct{
//     double ratio;
//     colour rgb;
// } ambient;

/* Light definition */
// typedef struct{
//     vector pos;
//     colour intensity;
//     double ratio;
// } light;

// plane
// typedef struct s_plane {
//     vector pos;
//     vector normal;
//     matrix transform;
//     double fov;
//     material material;
// } t_plane;

// cylinder
// typedef struct {
//     vector pos;
//     vector normal;
//     double diameter;
//     double max;
//     double min;
//     double height;
//     colour rgb;
//     matrix transform;
//     material material;
// } cylinder;

// typedef struct s_world {
//     light light;
//     sphere *s;
//     t_plane *p;
//     cylinder *cy;
// } t_world;

typedef struct s_intersect {
    void *object;
    char type;
    double t;
} t_intersect;

typedef struct s_comps {
    double t;
    void *object;
    char type;
    t_vector over_point;
    t_vector point;
    t_vector eyev;
    t_vector normalv;
    int inside;
} t_comps;

typedef vector point;

// mlx
void	my_mlx_pixel_put(t_world *data, int x, int y, int color);
int     create_trgb(int t, int r, int g, int b);

// vector functions
t_vector vectorSub(vector v1, vector v2);
double vectorDot(vector v1, vector v2);
t_vector vectorScale(vector v, double t);
t_vector vectorAdd(vector v1, vector v2);
t_vector normalize(vector v);
t_vector vectorInit(double x, double y, double z, double w);
t_vector vectorCross(vector a, vector b);
double magnitude(vector v);

// matrix functions
double determinant(matrix m);
t_matrix submatrix(matrix m, int row, int col);
double minor(matrix m, int rwo, int col);
double cofactor(double det, int row, int col);
double det(double **m);
double matrixDeterminant(matrix m);
t_matrix matrixMult(matrix m1, matrix m2);
t_matrix matrixTranspose(matrix m);
t_matrix matrixInverse(matrix m);

// matrix transformatons
t_vector translate(vector v, vector translator, int type);
t_vector scale(vector v, vector scaler, int type);
t_vector rotate_x(vector v, double r);
t_vector rotate_y(vector v, double r);
t_vector rotate_z(vector v, double r);
t_vector vector_mult_matrix (vector v, matrix m, int type);

// matrix inits
t_matrix matrixCreate(int rows, int cols);
t_matrix get_matrix(double x, double y, double z, char type);
t_matrix get_rotation_matrix(double r, int type);

// ray functions
vector position(ray r, double t);
ray transform(ray r, matrix m, int type);
ray ray_for_pixel(t_camera camera, int x, int y);

// sphere functions
sphere shpereInit();
double sphereIntersection(sphere s, ray r);
vector normal_at_sphere(sphere s, vector p);
vector reflect(vector in, vector normal);

// colour functions
colour colourInit(double r, double g, double b);
t_RGB stripe_at(vector point);
t_RGB
t_RGBht functions
t_RGBlightInit(vector pos, colour intensity);
t_RGB lightning(material m, light l, vector pos, vector v, vector n, int in_shadow);

// material functions
material materials();

// world functions
t_world worldInit(light l);
t_intersect intersect_world(t_world world , ray r);
t_comps prepare_computations (ray r, t_intersect i);
t_RGB shade_hit(t_world world, t_comps comps);
t_RGB color_at(t_world world, ray r);

// camera functions
t_camera cameraInit(double hsize, double wsize, double fov);
t_matrix view_transform(vector from, vector to, vector up);

// shadows functions
int is_shadowed(t_world world, vector point);

// render functions
// void render(t_camera camera, t_world world, t_world *img);

// plane functions
t_plane planeInit();
double planeIntersection(t_plane plane, ray r);
vector normal_at_plane(t_plane plane, vector p);

// cylinder functions
cylinder cylinderInit();
double cylinderIntersection(cylinder cy, ray r);
double cylinder_caps_intersect(cylinder cy, ray r);
vector normal_at_cylinder(cylinder cy, point p);

// test functions
void print_vector(vector v);
void print_matrix(matrix m);


#endif
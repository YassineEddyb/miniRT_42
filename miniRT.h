#ifndef MINIRT_H
# define MINIRT_H

#include "Includes/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <float.h>
#include <mlx.h>
#include <pthread.h>

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

// typedef vector point;

// mlx
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int     create_trgb(int t, int r, int g, int b);

// vector functions
t_vector vectorSub(t_vector v1, t_vector v2);
double vectorDot(t_vector v1, t_vector v2);
t_vector vectorScale(t_vector v, double t);
t_vector vectorAdd(t_vector v1, t_vector v2);
t_vector normalize(t_vector v);
t_vector vectorInit(double x, double y, double z, double w);
t_vector vectorCross(t_vector a, t_vector b);
double magnitude(t_vector v);

// matrix functions
double determinant(t_matrix m);
t_matrix submatrix(t_matrix m, int row, int col);
double minor(t_matrix m, int rwo, int col);
double cofactor(double det, int row, int col);
double det(double **m);
double matrixDeterminant(t_matrix m);
t_matrix matrixMult(t_matrix m1, t_matrix m2);
t_matrix matrixTranspose(t_matrix m);
t_matrix matrixInverse(t_matrix m);

// matrix transformatons
t_vector translate(t_vector v, t_vector translator, int type);
t_vector scale(t_vector v, t_vector scaler, int type);
t_vector rotate_x(t_vector v, double r);
t_vector rotate_y(t_vector v, double r);
t_vector rotate_z(t_vector v, double r);
t_vector vector_mult_matrix (t_vector v, t_matrix m, int type);

// matrix inits
t_matrix matrixCreate(int rows, int cols);
t_matrix get_matrix(double x, double y, double z, char type);
t_matrix get_rotation_matrix(double r, int type);

// ray functions
t_vector position(ray r, double t);
ray transform(ray r, t_matrix m, int type);
ray ray_for_pixel(t_camera camera, int x, int y);

// sphere functions
t_sphere shpereInit();
double sphereIntersection(t_sphere s, ray r);
t_vector normal_at_sphere(t_sphere s, t_vector p);
t_vector reflect(t_vector in, t_vector normal);

// colour functions
t_RGB colourInit(double r, double g, double b);
t_RGB stripe_at(t_vector point);


// color functions
t_light lightInit(t_vector pos, t_RGB intensity);
t_RGB lightning(t_material m, t_light l, t_vector pos, t_vector v, t_vector n, int in_shadow);

// material functions
t_material materials();

// world functions
t_world worldInit(t_light l);
t_intersect intersect_world(t_world world , ray r);
t_comps prepare_computations (ray r, t_intersect i);
t_RGB shade_hit(t_world world, t_comps comps);
t_RGB color_at(t_world world, ray r);

// camera functions
void cameraInit(t_camera *camera, double hsize, double vsize);
t_matrix view_transform(t_vector from, t_vector to, t_vector up);

// shadows functions
int is_shadowed(t_world world, t_vector point);

// render functions
// void render(t_camera camera, t_world world, t_world *img);

// plane functions
t_plane planeInit();
double planeIntersection(t_plane plane, ray r);
t_vector normal_at_plane(t_plane plane, t_vector p);

// cylinder functions
t_cy cylinderInit();
double cylinderIntersection(t_cy cy, ray r);
double cylinder_caps_intersect(t_cy cy, ray r);
t_vector normal_at_cylinder(t_cy cy, t_vector p);

// test functions
void print_vector(t_vector v);
void print_matrix(t_matrix m);


#endif
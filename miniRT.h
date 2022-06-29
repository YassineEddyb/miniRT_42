#ifndef MINIRT_H
# define MINIRT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <mlx.h>
#include <stdbool.h> /* Needed for boolean datatype */

# define WIDTH 1200
# define HEIGHT 700


#define RAY_T_MIN 0.0001f
#define RAY_T_MAX 1.0e30f

/* The vector structure */
typedef struct {
      float x,y,z;
} vector;

/* The sphere */
typedef struct s_sphere{
    vector pos;
    float  radius;
    float diameter;
    colour rgb;
} t_sphere; 

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

/* Colour definition */
typedef struct{
        float red, green, blue;
} colour;

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

typedef struct {
    vector pos;
    vector normal;
    float fov;
} plane;

typedef struct {
    vector pos;
    vector normal;
    float diameter;
    float height;
    colour rgb;
} cy;

typedef vector point;


#endif
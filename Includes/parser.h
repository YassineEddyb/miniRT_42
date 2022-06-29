#ifndef MINIRT_H
# define MINIRT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <mlx.h>
#include <fcntl.h>
#include <stdbool.h> /* Needed for boolean datatype */
#include "../srcs/libft/libft.h"

# define WIDTH 1200
# define HEIGHT 700


#define RAY_T_MIN 0.0001f
#define RAY_T_MAX 1.0e30f

/* t_RGB definition */
typedef struct s_RGB
{
	float	red;
	float	green;
	float	blue;

}	t_RGB;

/* The vector structure */
typedef struct s_vector
{
	float	x;
	float	y;
	float	z;

}	t_vector;

/* The sphere */
typedef struct s_sphere
{
	t_vector	pos;
	float		radius;
	float		diameter;
	t_RGB		rgb;

}	t_sphere; 

/* The ray */
typedef struct s_ray
{
	t_vector	start;
	t_vector	dir;

} t_ray;

// camera
typedef struct s_camera
{
	t_vector	pos;
	t_vector	normal;
	float		fov;

} t_camera;

typedef struct s_ambient
{
	float	ratio;
	t_RGB	rgb;

} t_ambient;

/* Light definition */
typedef struct s_light
{
	t_vector	pos;
	t_RGB		rgb;
	float		ratio;

}	t_light;

/* Material definition */
typedef struct s_material
{
	t_RGB	diffuse;
	float	reflection;

}	t_material; 

typedef struct s_plane
{
	t_vector	pos;
	t_vector	normal;
	float		fov;

}	t_plane;

typedef struct s_cy
{
	t_vector	pos;
	t_vector	normal;
	float		diameter;
	float		height;
	t_RGB		rgb;

} t_cy;

char	*get_next_line(int fd);
// typedef t_vector point;


#endif
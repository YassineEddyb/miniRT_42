/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 09:27:02 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/09/04 18:07:31 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "parser.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <float.h>
# include <mlx.h>
# include <pthread.h>

# define WIDTH 500
# define HEIGHT 500 
# define UNIT 10

# define EPSILON 0.0000001f
# define RAY_T_MIN 0.001f
# define RAY_T_MAX 1.0e30f

// mlx data
typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_delta {
	double	a;
	double	b;
	double	c;
	double	discriminant;	
}	t_delta;

typedef struct s_light_data {
	t_material	m;
	t_ambient	am;
	t_light		l;
	t_vector	pos;
}	t_light_data;

/* The t_ray */
typedef struct s_ray {
	t_vector	start;
	t_vector	dir;
}	t_ray;

typedef struct s_intersect {
	void	*object;
	char	type;
	double	t;
}	t_intersect;

typedef struct s_comps {
	double		t;
	void		*object;
	char		type;
	t_vector	over_point;
	t_vector	point;
	t_vector	eyev;
	t_vector	normalv;
	int			inside;
}	t_comps;

typedef struct s_th {
	pthread_t	th_id;
	int			max;
	int			min;
	t_world		world;
	t_camera	camera;
	t_data		*img;
}	t_th;

typedef struct s_phong {
	t_RGB		diffuse;
	t_RGB		specular;
	t_RGB		eff_color;
	t_vector	lightv;
	t_RGB		ambient;
	double		light_dot_n;
	double		light_diffuse;
}	t_phong;

// vector functions
t_vector	vector_sub(t_vector v1, t_vector v2);
double		vector_dot(t_vector v1, t_vector v2);
t_vector	vector_scale(t_vector v, double t);
t_vector	vector_add(t_vector v1, t_vector v2);
t_vector	normalize(t_vector v);
t_vector	vector_init(double x, double y, double z, double w);
t_vector	vector_cross(t_vector a, t_vector b);
double		magnitude(t_vector v);

// matrix functions
double		determinant(t_matrix m);
t_matrix	submatrix(t_matrix m, int row, int col);
double		minor(t_matrix m, int rwo, int col);
double		cofactor(double det, int row, int col);
double		det(double **m);
double		matrix_determinant(t_matrix m);
t_matrix	matrix_mult(t_matrix m1, t_matrix m2);
t_matrix	matrix_transpose(t_matrix m);
t_matrix	matrix_inverse(t_matrix m);

t_matrix	mult_matrix(t_matrix m1, t_matrix m2);

// matrix transformatons
t_vector	translate(t_vector v, t_vector translator, int type);
t_vector	scale(t_vector v, t_vector scaler, int type);
t_vector	rotate_x(t_vector v, double r);
t_vector	rotate_y(t_vector v, double r);
t_vector	rotate_z(t_vector v, double r);
t_vector	vector_mult_matrix(t_vector v, t_matrix m, int type);

// matrix inits
t_matrix	matrix_create(int rows, int cols);
t_matrix	get_matrix(double x, double y, double z, char type);
t_matrix	get_rotation_matrix(double r, int type);
void		init_light_data(t_light_data *data, t_world world, t_comps comps);

// t_ray functions
t_vector	position(t_ray r, double t);
t_ray		transform(t_ray r, t_matrix m, int type);
t_ray		ray_for_pixel(t_camera camera, int x, int y);

// sphere functions
void		sphere_init(t_sphere *sphere, t_ambient ambient);
double		sphere_intersection(t_sphere s, t_ray r);
t_vector	normal_at_sphere(t_sphere s, t_vector p);
t_vector	reflect(t_vector in, t_vector normal);

// color functions
t_RGB		color_init(double r, double g, double b);
t_RGB		stripe_at(t_plane plane, t_vector point);
t_RGB		mult_colors(t_RGB color1, t_RGB color2);
t_RGB		add_colors(t_RGB color1, t_RGB color2);
t_RGB		scale_colors(t_RGB color1, double scaler);

// light functions
void		light_init(t_light *light);
void		ambient_init(t_ambient *ambient);
t_RGB		lightning(t_light_data data, t_comps comps, int in_shadow);

// material functions
t_material	materials(t_RGB color, double ratio, double shininess);

// world functions
t_world		worldInit(t_light l);
t_intersect	intersect_world(t_world world, t_ray r);
t_comps		prepare_computations(t_ray r, t_intersect i);
t_RGB		shade_hit(t_world world, t_comps comps);
t_RGB		color_at(t_world world, t_ray r);

// camera functions
void		camera_init(t_camera *camera, double hsize, double vsize);
t_matrix	view_transform(t_vector from, t_vector to, t_vector up);

// shadows functions
int			is_shadowed(t_world world, t_vector point);

// render functions
void		*render(void *arg);

// Math functions
double		min(double a, double b);
double		rad(double deg);

// plane functions
void		plane_init(t_plane *plane, t_ambient ambient);
double		plane_intersection(t_plane plane, t_ray r);
t_vector	normal_at_plane(t_plane plane);

// cylinder functions
void		cylinder_init(t_cy *cy, t_ambient ambient);
double		cylinder_intersection(t_cy cy, t_ray r);
double		cylinder_caps_intersect(t_cy cy, t_ray r);
t_vector	normal_at_cylinder(t_cy cy, t_vector p);

// mlx helpers
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
int			close_window(void);
int			exit_program(int key);
int			create_trgb(int t, int r, int g, int b);

// free leaks funcion
void		free_matrix(t_matrix m);
void		free_objects(t_world *world);

// test functions
void		print_vector(t_vector v);
void		print_matrix(t_matrix m);

#endif
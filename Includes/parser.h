/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 12:07:24 by ael-bach          #+#    #+#             */
/*   Updated: 2022/09/11 11:55:00 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <mlx.h>
# include <fcntl.h>
# include <stdbool.h>
# include "../srcs/libft/libft.h"

/* t_RGB definition */
typedef struct s_RGB
{
	double		red;
	double		green;
	double		blue;

}	t_RGB;

typedef struct s_material
{
	t_RGB		color;
	double		ambient;
	double		diffuse;
	double		specular;
	double		shininess;
	double		reflective;

}	t_material;

typedef struct s_matrix
{
	int		rows;
	int		cols;
	double	**m;

}	t_matrix;

/* The vector structure */
typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
	double	w;

}	t_vector;

/* The sphere */
typedef struct s_sphere
{
	t_vector	pos;
	double		diameter;
	t_RGB		rgb;
	t_matrix	transform;
	t_matrix	inverted_transform;
	t_matrix	transposed_matrix;
	t_material	material;
	double		shiness;
	double		reflective;

}	t_sphere;

// camera
typedef struct s_camera
{
	t_vector	pos;
	t_vector	normal;
	double		fov;
	t_matrix	transform;
	t_matrix	inverted_transform;
	double		hsize;
	double		vsize;
	double		half_width;
	double		half_height;
	double		pixel_size;

}	t_camera;

typedef struct s_ambient
{
	double	ratio;
	t_RGB	rgb;

}	t_ambient;

/* Light definition */
typedef struct s_light
{
	t_vector	pos;
	t_RGB		rgb;
	double		ratio;

}	t_light;

typedef struct s_plane
{
	t_vector	pos;
	t_vector	normal;
	t_RGB		rgb;
	t_RGB		rgbcheck;
	char		stripe_type;
	t_matrix	transform;
	t_matrix	inverted_transform;
	t_matrix	transposed_matrix;
	t_material	material;
	double		shiness;
	double		reflective;

}	t_plane;

typedef struct s_cy
{
	t_vector	pos;
	t_vector	normal;
	double		diameter;
	double		height;
	t_RGB		rgb;
	double		max;
	double		min;
	t_material	material;
	t_matrix	transform;
	t_matrix	inverted_transform;
	t_matrix	transposed_matrix;
	double		shiness;
	double		reflective;

}	t_cy;

typedef struct s_cube {
	t_vector	pos;
	t_vector	normal;
	t_RGB		rgb;
	double		width;
	double		height;
	double		length;
	t_material	material;
	t_matrix	transform;
	t_matrix	inverted_transform;
	t_matrix	transposed_matrix;
	double		shiness;
	double		reflective;

} t_cube;

typedef struct s_index
{
	int		a;
	int		l;
	int		c;
	int		sp;
	int		pl;
	int		cy;
	int		cb;

}	t_index;

typedef struct s_v
{
	int	i;
	int	n;
	int	v;
	int	c;	

}	t_v;

typedef struct s_world
{
	t_ambient	**ambient;
	t_camera	**camera;
	t_light		**light;
	t_sphere	**sphere;
	t_plane		**plane;
	t_cube		**cube;
	t_cy		**cy;

}	t_world;

char		*get_next_line(int fd);
double		ft_atof(char *str);
void		free_two_arr(char **arr);
int			check_befor_atof(char *str);
void		error(char *str);
char		**ft_split_spaces(char const *s, char c);
void		check_rgbstring(char *str);
int			len_2d(char **str);
void		is_between(float small, float big, float nbr);
void		*check_rgb_value(t_RGB rgb);
void		*check_normalize_value(t_vector pos);

t_world		*allocate_data(t_index *index);
t_index		*count_index(char **file);
t_index		*fill_index(void);
t_world		*check_and_fill(char **file);
t_ambient	*ambient_light(char **str);
t_camera	*camera(char **info);
t_light		*light(char **info);
t_sphere	*sphere(char **tmp);
t_plane		*plane(char **tmp);
t_cy		*cylinder(char **tmp);
t_cube		*cube(char **tmp);
t_world		*parser(int ac, char **av);
t_vector	fill_vector(char **xyz, int _w, int dv);
t_RGB		plane_optional(char *tmp);
t_RGB		fill_rgb(char *tmp);

#endif
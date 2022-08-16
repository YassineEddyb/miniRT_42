#ifndef MINIRT_H
# define MINIRT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <mlx.h>
#include <fcntl.h>
#include <stdbool.h>
#include "../srcs/libft/libft.h"

# define WIDTH 1200
# define HEIGHT 700


#define RAY_T_MIN 0.0001f
#define RAY_T_MAX 1.0e30f

/* t_RGB definition */
typedef struct s_RGB
{
	int	red;
	int	green;
	int	blue;

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
	int			fov;

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
	t_RGB		rgb;

}	t_plane;

typedef struct s_cy
{
	t_vector	pos;
	t_vector	normal;
	float		diameter;
	float		height;
	t_RGB		rgb;

} t_cy;

typedef struct s_index
{
	int	A;
	int	L;
	int	C;
	int	sp;
	int	pl;
	int	cy;
	
}	t_index;

typedef struct s_data
{
	t_ambient	**A;
	t_camera	**C;
	t_light		**L;
	t_sphere	**sp;
	t_plane		**pl;
	t_cy		**cy;
	
}	t_data;


char		*get_next_line(int fd);
double 		ft_atof(char *str);
void		free_two_arr(char **arr);
int			check_befor_atof(char *str);
void		error(char *str);
char		**ft_split_spaces(char const *s, char c);
void		check_rgbstring(char *str);
int			len_2d(char **str);
void		is_between(float small, float big, float nbr);
void		*check_rgb_value(t_RGB rgb);
void		*check_normalize_value(t_vector pos);
t_data		*allocate_data(t_index *index);
t_index		*count_index(char **file);
t_index		*fill_index(void);
t_data		*check_and_fill(char **file);
t_ambient	*ambient_light(char **str);
t_camera	*camera(char **info);
t_light		*light(char **info);
t_sphere	*sphere(char **tmp);
t_plane		*plane(char **tmp);
t_cy		*cylinder(char **tmp);

#endif
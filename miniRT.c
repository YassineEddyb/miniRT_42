/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:25:43 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/08/02 18:49:32 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"


colour initColour(double red, double green, double blue)
{
	colour rgb;
	rgb.red = red;
	rgb.green = green;
	rgb.blue = blue;
	return (rgb);
}

/* Check if the ray and sphere intersect */
// int intersectRaySphere(ray *r, sphere *s)
// {
// 	double A = vectorDot(&r->dir, &r->dir);
// 	vector dist = vectorSub(&r->start, &s->pos);
// 	double B = 2 * vectorDot(&r->dir, &dist);
// 	double C = vectorDot(&dist, &dist) - (s->radius * s->radius);
// 	double discr = B * B - 4 * A * C;

// 	if(discr < 0)
// 		return (-1);
// 	else {
// 		double sqrtdiscr = sqrtf(discr);
// 		double t0 = (-B + sqrtdiscr)/(2);
// 		double t1 = (-B - sqrtdiscr)/(2);
// 		if(t0 > t1)
// 			t0 = t1;
// 		return t0;
// 	}
// }

void print_vector(vector v)
{
	printf("(x-> %f, y-> %f, z-> %f, w-> %f)\n\n", v.x, v.y, v.z, v.w);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}



// matrix get_transform_matrix(vector v, char t)
// {
// 	matrix m;
// 	m = matrixCreate(4, 4);
	
// }

int main(int argc, char **argv)
{
	void	*mlx;
	void	*win;
	double 	t;
	int x = 0, y = 0;
	double wall_size = 14.0;
	double half = wall_size / 2;
	double pixel_size = wall_size / WIDTH;
	double wall_z = 20;
	double t_close;
	
	t_world world;
	light l;
	t_camera camera;
	ray r;

	// light
	l = lightInit(vectorInit(-10, 10, -10, 0), initColour(1, 1, 1));

	// world
	world = worldInit(l);
	world.s[1].transform = get_matrix(vectorInit(-0.5, 1, 0.5, 0), 't');
	world.s[1].material.color = colourInit(1, 0, 0);

	world.s[0].transform = matrixMult(get_matrix(vectorInit(1.5, 0.5, -0.5, 0), 't'), get_matrix(vectorInit(0.5, 0.5, 0.5, 1), 's'));
	world.s[0].material.color = colourInit(0, 0, 1);

	world.s[2].transform = matrixMult(get_matrix(vectorInit(-1.5, 0.33, -0.75, 0), 't'), get_matrix(vectorInit(0.3, 0.3, 0.3, 1), 's'));
	world.s[2].material.color = colourInit(0, 1, 0);

	world.s[3].transform = get_matrix(vectorInit(10, 0.01, 10, 0), 's');
	world.s[3].material.color = colourInit(1, 0.9, 0.9);
	world.s[3].material.specular = 0;

	world.s[4].transform = matrixMult(matrixMult(matrixMult(get_matrix(vectorInit(0, 0, 5, 0), 't'), get_rotation_matrix(- M_PI / 4, 'y')),
							get_rotation_matrix(M_PI_2, 'x')), get_matrix(vectorInit(10, 0.01, 10, 1), 's'));
	world.s[4].material.color = colourInit(1, 0.9, 0.9);
	world.s[4].material.specular = 0;

	world.s[5].transform = matrixMult(matrixMult(matrixMult(get_matrix(vectorInit(0, 0, 5, 0), 't'), get_rotation_matrix(M_PI / 4, 'y')),
							get_rotation_matrix(M_PI_2, 'x')), get_matrix(vectorInit(10, 0.01, 10, 1), 's'));
	world.s[5].material.color = colourInit(1, 0.9, 0.9);
	world.s[5].material.specular = 0;

	// camera
	camera = cameraInit(WIDTH, HEIGHT, M_PI/3);

	// vectors
	vector from = vectorInit(0, 1.5, -5, 1);
	vector to = vectorInit(0, 1, 0, 1);
	vector up = vectorInit(0, 1, 0, 0);

	camera.transform = view_transform(from, to, up);

	// test
	// /test

	// mlx
	mlx = mlx_init();
	win = mlx_new_window(mlx, WIDTH, HEIGHT, "miniRT");
	void *img = mlx_new_image(mlx, WIDTH, HEIGHT);
	mlx_get_data_addr(img, )

	while(y < HEIGHT) {
		x = 0;
		while(x < WIDTH) {
			r = ray_for_pixel(camera, x, y);
			colour color = color_at(world, r);
			// printf("%f, %f, %f\n", color.red, color.green, color.blue);
			mlx_pixel_put(mlx, win, x, y, create_trgb(1, color.red * 255 , color.green * 255 , color.blue * 255));
			x++;
		}
		y++;
	}

	mlx_loop(mlx);
}

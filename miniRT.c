/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:25:43 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/08/09 20:34:30 by yed-dyb          ###   ########.fr       */
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

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int main(int argc, char **argv)
{
	void	*mlx;
	void	*win;
	double 	t;
	int x = 0, y = 0;

	t_data img;
	
	t_world world;
	light l;
	t_camera camera;
	ray r;

	// light
	l = lightInit(vectorInit(-10, 10, -10, 1), initColour(1, 1, 1));

	// world
	world = worldInit(l);
	world.s[0].transform = get_matrix(0, 1, 0.5, 't');
	world.s[0].material.color = colourInit(1, 0, 0);

	world.s[1].transform = matrixMult(get_matrix(1.5, 0.5, -0.5, 't'), get_matrix(0.5, 0.5, 0.5, 's'));
	world.s[1].material.color = colourInit(0, 0, 1);

	world.s[2].transform = matrixMult(get_matrix(-1.5, 0.33, -0.75, 't'), get_matrix(0.3, 0.3, 0.3, 's'));
	world.s[2].material.color = colourInit(0, 1, 0);

	// world.s[0].transform = get_matrix(vectorInit(10, 0.01, 10, 0), 's');
	// world.s[0].material.color = colourInit(1, 0.9, 0.9);
	// world.s[0].material.specular = 0;

	// world.s[4].transform = matrixMult(matrixMult(matrixMult(get_matrix(vectorInit(0, 0, 5, 0), 't'), get_rotation_matrix(- M_PI / 4, 'y')),
	// 						get_rotation_matrix(M_PI_2, 'x')), get_matrix(vectorInit(10, 0.01, 10, 1), 's'));
	// world.s[4].material.color = colourInit(1, 0.9, 0.9);
	// world.s[4].material.specular = 0;

	// world.s[5].transform = matrixMult(matrixMult(matrixMult(get_matrix(vectorInit(0, 0, 5, 0), 't'), get_rotation_matrix(M_PI / 4, 'y')),
	// 						get_rotation_matrix(M_PI_2, 'x')), get_matrix(vectorInit(10, 0.01, 10, 1), 's'));
	// world.s[5].material.color = colourInit(1, 0.9, 0.9);
	// world.s[5].material.specular = 0;

	// camera
	camera = cameraInit(WIDTH, HEIGHT, M_PI/3);

	// vectors
	vector from = vectorInit(0, 1.5, -5, 0);
	vector to = vectorInit(0, 1, 0, 0);
	vector up = vectorInit(0, 1, 0, 0);

	camera.transform = view_transform(from, to, up);


	// test ------------------------------
	// t_plane p = planeInit();
	// // p.transform = matrixMult(get_matrix(vectorInit(1, 0.5, 1, 1), 's'), get_rotation_matrix(M_PI/5, 'z'));
    // print_vector(normal_at_plane(p, vectorInit(10, 0, -10, 1)));
	// test ------------------------------

	// mlx
	mlx = mlx_init();
	win = mlx_new_window(mlx, WIDTH, HEIGHT, "miniRT");
	img.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	while(y < HEIGHT) {
		x = 0;
		while(x < WIDTH) {
			r = ray_for_pixel(camera, x, y);
			colour color = color_at(world, r);
			my_mlx_pixel_put(&img, x, y, create_trgb(1, color.red * 255 , color.green * 255 , color.blue * 255));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);

	mlx_loop(mlx);
}

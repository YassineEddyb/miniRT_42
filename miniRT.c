/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:25:43 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/08/16 18:53:19 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

typedef struct s_th {
	pthread_t th_id;
	int max;
	int min;
	t_world world;
	t_camera camera;
	t_data *img;
} t_th;

t_RGB initColour(double red, double green, double blue)
{
	t_RGB rgb;
	rgb.red = red;
	rgb.green = green;
	rgb.blue = blue;
	return (rgb);
}

void print_vector(t_vector v)
{
	printf("(x-> %f, y-> %f, z-> %f, w-> %f)\n\n", v.x, v.y, v.z, v.w);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void *render(void *arg)
{
	t_th *th;

	th = (t_th *)arg;

	ray r;
	int x, y = 0;

	while(y < HEIGHT)
	{
		x = th->min;
		while(x < th->max) {
			r = ray_for_pixel(th->camera, x, y);
			t_RGB color = color_at(th->world, r);
			my_mlx_pixel_put(th->img, x, y, create_trgb(1, color.red * 255 , color.green * 255 , color.blue * 255));
			x++;
		}
		y++;
	}

	return NULL;
}

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

	t_data img;
	
	// t_world world;
	// t_light l;
	t_camera camera;

	t_world *world = parser(argc, argv);

	// // light
	// l = lightInit(vectorInit(-1, 5, -1, 1), initColour(1, 1, 1));

	// // world
	// world = worldInit(l);
	// world.s[0].transform = get_matrix(0, 1, 0.5, 't');
	// world.s[0].material.color = colourInit(1, 0, 0);

	// world.s[1].transform = matrixMult(get_matrix(1.5, 0.5, -0.5, 't'), get_matrix(0.5, 0.5, 0.5, 's'));
	// world.s[1].material.color = colourInit(0, 0, 1);

	// world.s[2].transform = matrixMult(get_matrix(-1.5, 0.33, -0.75, 't'), get_matrix(0.3, 0.3, 0.3, 's'));
	// world.s[2].material.color = colourInit(0, 1, 0);

	// camera
	// camera = cameraInit(WIDTH, HEIGHT, M_PI/3);

	// // vectors
	// t_vector from = vectorInit(0, 3.5, -2, 0);
	// t_vector to = vectorInit(0, 1, 0, 0);
	// t_vector up = vectorInit(0, 1, 0, 0);

	// camera.transform = view_transform(from, to, up);

	/* test */
	// cylinder cy;

	// cy.min = 1;
	// cy.max = 2;
	// cy.transform = get_matrix(0, 0,0, 'i');

	// ray r;
	// r.start = vectorInit(0, 3, 0, 1);
	// r.dir = normalize(vectorInit(0, -1 , 0, 0));

	// printf("%f\n", cylinder_caps_intersect(cy, r));
	/* test */

	// mlx
	mlx = mlx_init();
	win = mlx_new_window(mlx, WIDTH, HEIGHT, "miniRT");
	img.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	t_th *th;
	int len = ceil(WIDTH / 50);

	th = malloc(len * sizeof(t_th));
	
	int i = 0;
	while(i < len)
	{
		th[i].min = i * 50;
		th[i].max = i * 50 + 50;
		th[i].camera = camera;
		th[i].world = *world;
		th[i].img = &img;
		
		// printf("len %d, min : %d, max = %d\n", len, th[i].min, th[i].max);

		pthread_create(&(th[i].th_id), NULL, render, &(th[i]));
		i++;
	}

	i = -1;
	while(++i < len)
		pthread_join(th[i].th_id, NULL);

	mlx_put_image_to_window(mlx, win, img.img, 0, 0);

	mlx_loop(mlx);
}

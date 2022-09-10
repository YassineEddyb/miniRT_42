/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:25:43 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/09/10 19:44:05 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/miniRT.h"

double	min(double a, double b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

double	rad(double deg)
{
	return (deg * M_PI_2);
}

void	init_objects(t_world *world)
{
	int	i;

	i = 0;
	while (world->sphere[i])
	{
		sphere_init(world->sphere[i], *(world->ambient[0]));
		i++;
	}
	i = 0;
	while (world->plane[i])
	{
		plane_init(world->plane[i], *(world->ambient[0]));
		i++;
	}
	i = 0;
	while (world->cy[i])
	{
		cylinder_init(world->cy[i], *(world->ambient[0]));
		i++;
	}
	i = 0;
	while (world->cube[i])
	{
		cube_init(world->cube[i], *(world->ambient[0]));
		i++;
	}
	i = 0;
	while (world->light[i])
	{
		light_init(world->light[i]);
		i++;
	}
	camera_init(*(world->camera), WIDTH, HEIGHT);
	ambient_init(*(world->ambient));
}

void	create_threads(t_world *world, t_data *img)
{
	int		i;
	t_th	*th;
	int		len;

	len = ceil(WIDTH / THREAD);
	th = malloc((len + 1) * sizeof(t_th));
	i = 0;
	while (i < len + 1)
	{
		th[i].min = i * THREAD;
		if (i * THREAD + THREAD < WIDTH)
			th[i].max = i * THREAD + THREAD;
		else
			th[i].max = WIDTH;
		th[i].camera = *(world->camera[0]);
		th[i].world = *world;
		th[i].img = img;
		pthread_create(&(th[i].th_id), NULL, render, &(th[i]));
		i++;
	}
	i = -1;
	while (++i < len)
		pthread_join(th[i].th_id, NULL);
	free(th);
}

int	main(int argc, char **argv)
{
	void	*mlx;
	void	*win;
	t_data	img;
	t_world	*world;

	world = parser(argc, argv);
	init_objects(world);
	// test
	// t_ray r;
	// r.start = vector_init(5, 0.5, 0, 1);
	// r.dir = vector_init(-1, 0, 0, 0);

	// t_vector v = normal_at_cube(*(world->cube[0]), vector_init(1, -0.9, 0.2, 1));

	// printf("%f, %f, %f\n", v.x, v.y, v.z);

	mlx = mlx_init();
	win = mlx_new_window(mlx, WIDTH, HEIGHT, "miniRT");
	img.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img,
			&img.bits_per_pixel, &img.line_length, &img.endian);
	create_threads(world, &img);
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
	mlx_hook(win, 17, 0, close_window, NULL);
	mlx_key_hook(win, exit_program, NULL);
	free_objects(world);
	mlx_loop(mlx);
}

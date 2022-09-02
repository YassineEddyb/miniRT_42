/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <ael-bach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:25:43 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/09/02 17:11:20 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	min(double a, double b)
{
	if (a < b)
		return (a);
	else
		return (b);
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
	camera_init(*(world->camera), WIDTH, HEIGHT);
	light_init(*(world->light));
	ambient_init(*(world->ambient));
}

void	create_threads(t_world *world, t_data *img)
{
	int		i;
	t_th	*th;
	int		len;

	len = ceil(WIDTH / 100);
	th = malloc(len * sizeof(t_th));
	i = 0;
	while (i < len)
	{
		th[i].min = i * 100;
		th[i].max = i * 100 + 100;
		th[i].camera = *(world->camera[0]);
		th[i].world = *world;
		th[i].img = img;
		pthread_create(&(th[i].th_id), NULL, render, &(th[i]));
		i++;
	}
	i = -1;
	while (++i < len)
		pthread_join(th[i].th_id, NULL);
}

int	main(int argc, char **argv)
{
	void	*mlx;
	void	*win;
	t_data	img;
	t_world	*world;

	world = parser(argc, argv);
	init_objects(world);
	mlx = mlx_init();
	win = mlx_new_window(mlx, WIDTH, HEIGHT, "miniRT");
	img.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img,
			&img.bits_per_pixel, &img.line_length, &img.endian);
	create_threads(world, &img);
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
	mlx_hook(win, 17, 0, close_window, NULL);
	mlx_key_hook(win, exit_program, NULL);
	mlx_loop(mlx);
}

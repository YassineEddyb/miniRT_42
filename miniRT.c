/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:25:43 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/09/01 14:52:14 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	*render(void *arg)
{
	t_th	*th;
	ray		r;
	t_RGB	color;
	int		x;
	int		y;

	th = (t_th *)arg;
	y = 0;
	while (y < HEIGHT)
	{
		x = th->min;
		while (x < th->max)
		{
			r = ray_for_pixel(th->camera, x, y);
			color = color_at(th->world, r);
			my_mlx_pixel_put(th->img, x, y, create_trgb(1,
					min(color.red * 255, 255),
					min(color.green * 255, 255),
					min(color.blue * 255, 255)));
			x++;
		}
		y++;
	}
	return (NULL);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
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
	mlx_loop(mlx);
}

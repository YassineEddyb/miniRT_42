/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 14:59:49 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/09/04 15:21:27 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/miniRT.h"

// render the scene
void	*render(void *arg)
{
	t_th	*th;
	t_ray	r;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 15:42:08 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/08/31 11:07:03 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	is_shadowed(t_world world, t_vector point)
{
	ray			r;
	t_intersect	intersect;
	t_vector	v;
	t_vector	dir;
	int			i;

	i = 0;
	while (world.light[i])
	{
		v = vector_sub((**world.light).pos, point);
		dir = normalize(v);
		r.start = point;
		r.dir = dir;
		intersect = intersect_world(world, r);
		if (intersect.t != -1 && intersect.t < magnitude(v))
			return (1);
		i++;
	}
	return (0);
}

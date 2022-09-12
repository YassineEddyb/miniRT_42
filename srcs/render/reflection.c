/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 10:51:43 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/09/11 10:17:40 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/miniRT.h"

t_RGB reflect_color(t_world world, t_comps comps, int remaining)
{
	t_sphere		*s;
	t_plane			*p;
	t_cy			*cy;
	t_cube			*cube;
	double			reflective;

	if (remaining <= 0)
		return (color_init(0, 0, 0));
	if (comps.type == 's')
	{
		s = (t_sphere *)comps.object;
        if (s->material.reflective == 0)
            return (color_init(0, 0, 0));
		reflective = s->material.reflective;
	}
	else if (comps.type == 'p')
	{
		p = (t_plane *)comps.object;
		if (p->material.reflective == 0)
            return (color_init(0, 0, 0));
		reflective = p->material.reflective;
	}
	else if (comps.type == 'c')
	{
		cy = (t_cy *)comps.object;
		if (cy->material.reflective == 0)
            return (color_init(0, 0, 0));
		reflective = cy->material.reflective;
	}
	else
	{
		cube = (t_cube *)comps.object;
		if (cube->material.reflective == 0)
            return (color_init(0, 0, 0));
		reflective = cube->material.reflective;
	}

	t_ray reflect_ray;
	reflect_ray.start = comps.over_point;
	reflect_ray.dir = comps.reflectv;
	
	t_RGB color = color_at(world, reflect_ray, remaining - 1);

	return (scale_colors(color, reflective));
}
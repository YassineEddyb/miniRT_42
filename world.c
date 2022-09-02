/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <ael-bach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 14:24:04 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/09/02 12:50:17 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// set the instersected object data
void	intersect_object(t_intersect *intersect, double t, void *obj, char type)
{
	if ((t < intersect->t && t != -1) || (intersect->t == -1 && t != -1))
	{
		intersect->t = t;
		intersect->object = obj;
		intersect->type = type;
	}
}

// the nearest t_ray intersection in this world
t_intersect	intersect_world(t_world world, t_ray r)
{
	int			i;
	double		t;
	t_intersect	intersect;

	intersect.t = -1;
	i = -1;
	while (world.sphere[++i])
	{
		t = sphere_intersection(*(world.sphere[i]), r);
		intersect_object(&intersect, t, (void *)world.sphere[i], 's');
	}
	i = -1;
	while (world.plane[++i])
	{
		t = plane_intersection(*(world.plane[i]), r);
		intersect_object(&intersect, t, (void *)world.plane[i], 'p');
	}
	i = -1;
	while (world.cy[++i])
	{
		t = cylinder_intersection(*(world.cy[i]), r);
		intersect_object(&intersect, t, (void *)world.cy[i], 'c');
	}
	return (intersect);
}

// get the information neaded for the intesected object;
t_comps	prepare_computations(t_ray r, t_intersect i)
{
	t_comps	comps;

	comps.t = i.t;
	comps.object = i.object;
	comps.type = i.type;
	comps.point = position(r, i.t);
	comps.eyev = vector_scale(r.dir, -1);
	if (i.type == 's')
		comps.normalv = normal_at_sphere(*((t_sphere *)i.object), comps.point);
	else if (i.type == 'p')
		comps.normalv = normal_at_plane(*((t_plane *)i.object));
	else if (i.type == 'c')
		comps.normalv = normal_at_cylinder(*((t_cy *)i.object), comps.point);
	comps.over_point = vector_add(
			comps.point, vector_scale(comps.normalv, FLT_EPSILON));
	return (comps);
}

t_RGB	shade_hit(t_world world, t_comps comps)
{
	t_sphere		*s;
	t_plane			*p;
	t_cy			*cy;
	t_light_data	data;

	init_light_data(&data, world, comps);
	if (comps.type == 's')
	{
		s = (t_sphere *)comps.object;
		data.m = s->material;
		return (lightning(data, comps, is_shadowed(world, data.pos)));
	}
	else if (comps.type == 'p')
	{
		p = (t_plane *)comps.object;
		data.m = p->material;
		return (lightning(data, comps, is_shadowed(world, data.pos)));
	}
	else if (comps.type == 'c')
	{
		cy = (t_cy *)comps.object;
		data.m = cy->material;
		return (lightning(data, comps, is_shadowed(world, data.pos)));
	}
	return (color_init(0, 0, 0));
}

// get the color at the intersection of the t_ray with the sphere
t_RGB	color_at(t_world world, t_ray r)
{
	t_intersect	i;
	t_comps		comps;
	t_RGB		c;

	i = intersect_world(world, r);
	if (i.t < 0)
		return (color_init(0, 0, 0));
	comps = prepare_computations(r, i);
	c = shade_hit(world, comps);
	return (c);
}

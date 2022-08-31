/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 14:24:04 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/08/31 14:05:04 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"


// the nearest ray intersection in this world
t_intersect intersect_world(t_world world , ray r)
{
    int i;
    t_intersect intersect;
    intersect.t = -1;
    double tmp;

    i = 0;
    while(world.sphere[i])
    {
        tmp = sphere_intersection(*(world.sphere[i]), r);
        if ((tmp < intersect.t && tmp != -1) || (intersect.t == -1 && tmp != -1))
        {
            intersect.t = tmp;
            intersect.object = (void *)world.sphere[i];
            intersect.type = 's';
        }
        i++;
    }

    i = 0;
    while(world.plane[i])
    {
        tmp = plane_intersection(*(world.plane[i]), r);
        if ((tmp < intersect.t && tmp != -1) || (intersect.t == -1 && tmp != -1))
        {
            intersect.t = tmp;
            intersect.object = (void *)world.plane[i];
            intersect.type = 'p';
        }
        i++;
    }

    i = 0;
    while(world.cy[i])
    {
        tmp = cylinder_intersection(*(world.cy[i]), r);
        if ((tmp < intersect.t && tmp != -1) || (intersect.t == -1 && tmp != -1))
        {
            intersect.t = tmp;
            intersect.object = (void *)world.cy[i];
            intersect.type = 'c';
        }
        i++;
    }

    return intersect;
}

// get the information neaded for the intesected object;
t_comps prepare_computations (ray r, t_intersect i)
{
    t_comps comps;

    comps.t = i.t;
    comps.object = i.object;
    comps.type = i.type;
    comps.point = position(r, i.t);
    comps.eyev = vector_scale(r.dir, -1);
    if (i.type == 's')
        comps.normalv = normal_at_sphere(*((t_sphere *)i.object), comps.point);
    else if (i.type == 'p')
        comps.normalv = normal_at_plane(*((t_plane *)i.object), comps.point);
    else if (i.type == 'c')
        comps.normalv = normal_at_cylinder(*((t_cy *)i.object), comps.point);

    comps.over_point = vector_add(comps.point, vector_scale(comps.normalv, FLT_EPSILON));

    return comps;
}

t_RGB shade_hit(t_world world, t_comps comps)
{
    t_sphere *s;
    t_plane *p;
    t_cy *cy;
    t_light_data light_data;

    light_data.am = **(world.ambient);
    light_data.l = **(world.light);
    light_data.pos = comps.over_point;
    light_data.eyev = comps.eyev;
    light_data.normalv = comps.normalv;
    if (comps.type == 's')
    {
        s = (t_sphere *)comps.object;
        light_data.m = s->material;
        return lightning(light_data, is_shadowed(world, comps.over_point));
    }
    else if (comps.type == 'p')
    {
        p = (t_plane *)comps.object;
        light_data.m = p->material;
        // p->material.color = stripe_at(comps.point);
        return lightning(light_data, is_shadowed(world, comps.over_point));
    }
    else if (comps.type == 'c')
    {
        cy = (t_cy *)comps.object;
        light_data.m = cy->material;
        return lightning(light_data, is_shadowed(world, comps.over_point));
    } 
}

// get the color at the intersection of the ray with the sphere
t_RGB color_at(t_world world, ray r)
{
    t_intersect i = intersect_world(world, r);

    if (i.t < 0)
        return colour_init(0,0,0);

	t_comps comps = prepare_computations(r, i);

	t_RGB c = shade_hit(world, comps);

    return c;
}
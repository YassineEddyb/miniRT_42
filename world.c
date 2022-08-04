/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 14:24:04 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/08/04 16:18:40 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// create a new world
t_world worldInit(light l)
{
    t_world world;

    world.s = malloc(6 * sizeof(sphere));
    world.p = malloc(1 * sizeof(t_plane));

    world.s[0] = shpereInit();
    world.s[1] = shpereInit();
    // world.s[2] = shpereInit();
    // world.s[3] = shpereInit();
    // world.s[4] = shpereInit();
    // world.s[5] = shpereInit();
    world.light = l;

    return world;
}


// the nearest ray intersection in this world
t_intersect intersect_world(t_world world , ray r)
{
    int i;
    t_intersect intersect;
    intersect.t = sphereIntersection(r, world.s[0]);
    intersect.object = (void *)(&world.s[0]);
    intersect.type = 's';
    double tmp = intersect.t;

    i = 1;
    while(i < 2)
    {
        tmp = sphereIntersection(r, world.s[i]);
        if ((tmp < intersect.t && tmp != -1) || (intersect.t == -1 && tmp != -1))
        {
            intersect.t = tmp;
            intersect.object = (void *)(&world.s[i]);
            intersect.type = 's';
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
    comps.eyev = vectorScale(r.dir, -1);
    comps.normalv = normal_at_sphere(*((sphere *)i.object), comps.point);
    comps.over_point = vectorAdd(comps.point, vectorScale(comps.normalv, 0.0000000001f));

    // if (vectorDot(comps.normalv, comps.eyev) < 0)
    // {
    //     comps.inside = 1;
    //     comps.normalv = vectorScale(comps.normalv, -1);
    // } else
    //     comps.inside = 0;

    return comps;
}

colour shade_hit(t_world world, t_comps comps)
{
    sphere *s;
    // plane *p;
    // cylinder *c;
    if (comps.type == 's')
    {
        s = (sphere *)comps.object;
        return lightning(s->material, world.light, comps.over_point, comps.eyev, comps.normalv, is_shadowed(world, comps.over_point));
    }
    // else if (comps.type == 'p')
    // {
    //     p = (plane *)comps.object;
    //     return lightning(p->material, world.light, comps.point, comps.eyev, comps.normalv);
    // } else {
    //     s = (sphere *)comps.object;
    //     return lightning(s->material, world.light, comps.point, comps.eyev, comps.normalv);
    // }
}

// get the color at the intersection of the ray with the sphere
colour color_at(t_world world, ray r)
{
    t_intersect i = intersect_world(world, r);

    if (i.t < 0)
        return colourInit(0,0,0);

	t_comps comps = prepare_computations(r, i);

	colour c = shade_hit(world, comps);

    return c;
}
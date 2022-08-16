/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 14:24:04 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/08/16 18:41:10 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// create a new world
// t_world worldInit(t_light l)
// {
//     t_world world;

//     world.sphere = malloc(3 * sizeof(sphere));
//     world.pa = malloc(4 * sizeof(t_plane));
//     world.cy = malloc(2 * sizeof(cylinder));

//     world.s[0] = shpereInit();
//     world.p[0] = planeInit();
//     world.p[0].material.color = colourInit(0, 0.54, 0.54);
//     world.p[1] = planeInit();
//     world.p[1].transform = matrixMult(get_matrix(0, 0, 4, 't'), get_rotation_matrix(M_PI / 2, 'x'));
//     world.p[1].material.color = colourInit(0.91, 0.58, 0.47);
//     world.p[2] = planeInit();
//     world.p[2].transform = matrixMult(get_matrix(4, 0, 0, 't'), get_rotation_matrix(M_PI / 2.5, 'z'));
//     world.p[2].material.color = colourInit(0.11, 0.56, 1);
//     world.p[3] = planeInit();
//     world.p[3].transform = matrixMult(get_matrix(-4, 0, 0, 't'), get_rotation_matrix(M_PI / 2.5, 'z'));
//     world.p[3].material.color = colourInit(0.11, 0.56, 1);
//     // world.p[1].material.color = colourInit(0.3, 0.8, 0.9);
//     // world.p[3].transform =  matrixMult(get_matrix(-10, 0, 0, 't'), get_rotation_matrix(M_PI_2, 'z'));
//     // world.p[3].material.color = colourInit(0.3, 0.8, 0.9);
//     // world.p[2].transform =  matrixMult(get_matrix(10, 0, 0, 't'), get_rotation_matrix(M_PI_2, 'z'));
//     // world.p[2].material.color = colourInit(0.3, 0.8, 0.9);
//     world.cy[0] = cylinderInit();
//     // world.cy[0].transform = get_matrix(2, 0, 0, 't');
//     world.cy[0].diameter = 1;

//     world.light = l;

//     return world;
// }


// the nearest ray intersection in this world
t_intersect intersect_world(t_world world , ray r)
{
    int i;
    t_intersect intersect;
    intersect.t = -1;
    double tmp;

    i = 0;
    while(i < 0)
    {
        tmp = sphereIntersection(*(world.sphere[i]), r);
        if ((tmp < intersect.t && tmp != -1) || (intersect.t == -1 && tmp != -1))
        {
            intersect.t = tmp;
            intersect.object = (void *)(&world.sphere[i]);
            intersect.type = 's';
        }
        i++;
    }

    i = 0;
    while(i < 4)
    {
        tmp = planeIntersection(*(world.plane[i]), r);
        if ((tmp < intersect.t && tmp != -1) || (intersect.t == -1 && tmp != -1))
        {
            intersect.t = tmp;
            intersect.object = (void *)(&world.plane[i]);
            intersect.type = 'p';
        }
        i++;
    }

    i = 0;
    while(i < 1)
    {
        tmp = cylinder_caps_intersect(*(world.cy[i]), r);
        if ((tmp < intersect.t && tmp != -1) || (intersect.t == -1 && tmp != -1))
        {
            intersect.t = tmp;
            intersect.object = (void *)(&world.cy[i]);
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
    comps.eyev = vectorScale(r.dir, -1);
    if (i.type == 's')
        comps.normalv = normal_at_sphere(*((t_sphere *)i.object), comps.point);
    else if (i.type == 'p')
        comps.normalv = normal_at_plane(*((t_plane *)i.object), comps.point);
    else if (i.type == 'c')
        comps.normalv = normal_at_cylinder(*((t_cy *)i.object), comps.point);

    comps.over_point = vectorAdd(comps.point, vectorScale(comps.normalv, EPSILON));

    // if (vectorDot(comps.normalv, comps.eyev) < 0)
    // {
    //     comps.inside = 1;
    //     comps.normalv = vectorScale(comps.normalv, -1);
    // } else
    //     comps.inside = 0;

    return comps;
}

t_RGB shade_hit(t_world world, t_comps comps)
{
    t_sphere *s;
    t_plane *p;
    t_cy *cy;
    if (comps.type == 's')
    {
        s = (t_sphere *)comps.object;
        return lightning(s->material, **(world.light), comps.over_point, comps.eyev, comps.normalv, is_shadowed(world, comps.over_point));
    }
    else if (comps.type == 'p')
    {
        p = (t_plane *)comps.object;
        // p->material.color = stripe_at(comps.point);
        return lightning(p->material, **(world.light), comps.over_point, comps.eyev, comps.normalv, is_shadowed(world, comps.over_point));
    }
    else if (comps.type == 'c')
    {
        cy = (t_cy *)comps.object;
        return lightning(cy->material, **(world.light), comps.over_point, comps.eyev, comps.normalv, is_shadowed(world, comps.over_point));
    } 
}

// get the color at the intersection of the ray with the sphere
t_RGB color_at(t_world world, ray r)
{
    t_intersect i = intersect_world(world, r);

    if (i.t < 0)
        return colourInit(0,0,0);

	t_comps comps = prepare_computations(r, i);

	t_RGB c = shade_hit(world, comps);

    return c;
}
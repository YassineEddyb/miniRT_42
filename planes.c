/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   planes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:14:47 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/08/20 11:37:44 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void planeInit(t_plane *plane, t_ambient ambient)
{
    plane->transform = matrixMult(matrixMult(matrixMult(
                        get_rotation_matrix(plane->normal.y * M_PI_2, 'y'),
                        get_matrix(plane->pos.x, plane->pos.y, plane->pos.z, 't')),
                        get_rotation_matrix(plane->normal.x * M_PI_2, 'z')),
                        get_rotation_matrix(plane->normal.z * M_PI_2, 'x'));
    plane->pos = vectorInit(0, 0, 0, 1);
    plane->material = materials(plane->rgb, ambient.ratio);
}

double planeIntersection(t_plane plane, ray r)
{
    ray r2;
    double t;

    r2 = transform(r, plane.transform, -1);

    if (fabs(r2.dir.y) < 0.001f)
        return (-1);
    
    t = -r2.start.y / r2.dir.y;
    
    if (t > 0.001f) return (t);
    else return (-1);

}


t_vector normal_at_plane(t_plane plane, t_vector p)
{
    // t_vector obj_p = vector_mult_matrix(p, plane.transform, -1);
    // // if (obj_p.x == p.x && obj_p.y == p.y && obj_p.z == p.z)
    // //     return vectorInit(0, 1, 0, 0);
    // t_vector obj_n = vectorInit(obj_p.x, obj_p.y, obj_p.z, 0);
    t_vector world_n = vector_mult_matrix(plane.normal, matrixTranspose(matrixInverse(plane.transform)), 1);

    world_n.w = 0;

    return normalize(world_n);
    // return vectorInit(0, 1, 0, 0);
}
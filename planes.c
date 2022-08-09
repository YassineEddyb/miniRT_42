/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   planes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:14:47 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/08/09 13:59:47 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_plane planeInit()
{
    t_plane p;

    p.pos = vectorInit(0, 0, 0, 1);
    p.transform = get_matrix(0, 0, 0, 'i');
    p.material = materials();

    return p;
}

double planeIntersection(ray r, t_plane plane)
{
    ray r2;
    double t;

    r2 = transform(r, plane.transform, -1);

    if (fabs(r2.dir.y) < 0.001f)
        return (-1);
    
    t = -r2.start.y / r2.dir.y;
    
    if (t > 0.001f)
        return (t);
    else return (-1);

}


vector normal_at_plane(t_plane plane, vector p)
{
    // vector obj_p = vector_mult_matrix(p, plane.transform, -1);
    
    // vector obj_n = vectorInit(obj_p.x, obj_p.y, obj_p.z, 0);
    // vector world_n = vector_mult_matrix(obj_n, matrixTranspose(matrixInverse(plane.transform)), 1);

    // world_n.w = 0;

    // return normalize(world_n);
    return vectorInit(0, 1, 0, 0);
}
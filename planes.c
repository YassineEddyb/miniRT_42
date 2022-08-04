/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   planes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:14:47 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/08/04 16:15:16 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_plane planeInit()
{
    t_plane p;

    p.pos = vectorInit(0, 0, 0, 1);
    p.transform = get_matrix(vectorInit(0, 0, 0, 0), 'i');
    p.material = materials();

    return p;
}

float planeIntersection(ray r, t_plane plane)
{
    ray r2;

    r2 = transform(r, plane.transform, -1);

    if (fabs(r2.dir.y) < 0.001f)
        return (-1);
    
    return (-r2.start.y / r2.dir.y);
}

vector normal_at_plane(t_plane plane, vector p) {
    vector obj_p = vector_mult_matrix(p, plane.transform, -1);
    vector obj_n = vectorSub(obj_p, plane.pos);
    vector world_n = vector_mult_matrix(obj_n, matrixTranspose(matrixInverse(plane.transform)), 1);

    world_n.w = 0;

    return normalize(world_n);
}
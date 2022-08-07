/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 15:42:08 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/08/07 14:41:32 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int is_shadowed(t_world world, vector point)
{
    ray r;
    t_intersect intersect;

    vector v = vectorSub(world.light.pos, point);
    double distance = magnitude(v);
    vector dir = normalize(v);

    r.start = point;
    r.dir = dir;

    intersect = intersect_world(world, r);

    printf("%f\n", intersect.t);

    if (intersect.t != -1 && intersect.t < distance)
        return 1;
    else
        return 0;
}
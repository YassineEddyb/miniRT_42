/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 23:30:25 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/07/25 13:45:24 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

vector position(ray r, float t)
{
    return (vectorAdd(r.start, vectorScale(r.dir, t)));
}

ray transform(ray r, vector v, char t, int type)
{
    ray new_ray;

    if (t == 't')
    {
        new_ray.start = translate(r.start, v, type);
	    new_ray.dir = translate(r.dir, v, type);
    } 
    else if (t == 's')
    {
        new_ray.start = scale(r.start, v, type);
	    new_ray.dir = scale(r.dir, v, type);
    }

    return (new_ray);
}

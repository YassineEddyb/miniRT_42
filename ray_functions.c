/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 23:30:25 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/08/02 16:20:57 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// get the position where the intersection occured
vector position(ray r, double t)
{
    return (vectorAdd(r.start, vectorScale(r.dir, t)));
}

// transform the ray
ray transform(ray r, matrix m, int type)
{
    ray new_ray;

    new_ray.start = vector_mult_matrix(r.start, m, type);
    new_ray.dir = vector_mult_matrix(r.dir, m, type);

    return (new_ray);
}

// get the ray tha passes through x ans y
ray ray_for_pixel(t_camera camera, int x, int y)
{
    ray r;
    double xoffset = (x + 0.5)* camera.pixel_size;
    double yoffset = (y + 0.5)* camera.pixel_size;

    double world_x = camera.half_width - xoffset;
    double world_y = camera.half_height - yoffset;

    vector pixel = vector_mult_matrix(vectorInit(world_x, world_y, -1, 1), camera.transform, -1);

    r.start = vector_mult_matrix(vectorInit(0,0,0,1), camera.transform, -1);
    r.dir = normalize(vectorSub(pixel, r.start));

    return (r);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 12:57:49 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/07/25 16:20:30 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// sphere sphereInit(vector transform)
// {
//     sphere s;
//     s.pos = vectorInit(0, 0, 0, 1);
//     return s;
// }

float sphereIntersection(ray r, sphere s)
{
    float A;
    float B;
    float C;
    float t1;
    float t2;
    vector v;
    float tmp;
    float discriminant;
    ray r2;

    r2 = transform(r, s.transform.transform, s.transform.type, -1);
    // t = malloc(sizeof(float) * 2);

    v = vectorSub(r2.start, s.pos);
    A = vectorDot(r2.dir, r2.dir);
    B = 2 * vectorDot(r2.dir, v);
    C = vectorDot(v, v) - 1;
    discriminant =  B * B - 4 * A * C; 
    
    if (discriminant < 0)
        return (-1);
    else
    {
        t1 = (-B - sqrt(discriminant)) / (2 * A);
        t2 = (-B + sqrt(discriminant)) / (2 * A);

        if (t1 > t2)
            return t2;
        else 
            return t1;
    }
}

sphere shpereInit()
{
    sphere s;

    s.pos = vectorInit(0,0, 0, 1);
    s.transform.transform = vectorInit(0,0,0,1);
    s.transform.type = 't';

    return s;
}
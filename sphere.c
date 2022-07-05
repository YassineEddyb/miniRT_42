/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 12:57:49 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/07/04 17:45:52 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// sphere sphereInit(vector transform)
// {
//     sphere s;
//     s.pos = vectorInit(0, 0, 0, 1);
//     return s;
// }

float *sphereIntersection(ray r, sphere s)
{
    float A;
    float B;
    float C;
    float *t;
    vector v;
    float tmp;
    float discriminant;

    t = malloc(sizeof(float) * 2);

    v = vectorSub(r.start, s.pos);
    A = vectorDot(r.dir, r.dir);
    B = 2 * vectorDot(r.dir, v);
    C = vectorDot(v, v) - 1;
    discriminant =  B * B - 4 * A * C; 
    
    if (determinant < 0)
        return (NULL);
    else
    {
        t[0] = (-B - sqrt(discriminant)) / (2 * A);
        t[1] = (-B + sqrt(discriminant)) / (2 * A);

        if (t[0] > t[1])
        {
            tmp = t[0];
            t[0] = t[1];
            t[1] = tmp;
        }
        return (t);
    }
}
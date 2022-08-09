/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 21:14:35 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/08/08 20:51:30 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

cylinder cylinderInit()
{
    cylinder cy;

    cy.transform = get_matrix(0, 0, 0, 'i');
    cy.material = materials();
    cy.min = -1;
    cy.max = 2;

    return cy;
}

float cylinderIntersection(ray r, cylinder cy)
{
    ray r2;
    double t0, t1;

    r2 = transform(r, cy.transform, -1);

    double a = r2.dir.x * r2.dir.x + r2.dir.z * r2.dir.z;
    
    if (a < 0.001f)
        return (-1);
    
    double b = 2 * r2.start.x * r2.dir.x + 2 * r2.start.z * r2.dir.z;
    double c = r2.start.x * r2.start.x + r.start.z * r.start.z - 1;

    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return (-1);
    else
    {
        t0 = (-b - sqrt(discriminant)) / (2 * a);
        t1 = (-b + sqrt(discriminant)) / (2 * a);

        if(t0 > t1)
            t0 = t1;

        double y0 = r2.start.y + t0 * r2.dir.y;
        double y1 = r2.start.y + t1 * r2.dir.y;
        if (t0 > 0.001f && cy.min < y0 && y0 < cy.max)
            return (t0);
        else if (t1 > 0.001f && cy.min < y1 && y1 < cy.max)
            return (t1);
        else return (-1);
    }
}

vector normal_at_cylinder(cylinder cy, point p)
{
    vector obj_p = vector_mult_matrix(p, cy.transform, -1);
    vector obj_n = vectorInit(obj_p.x, 0, obj_p.z, 1);
    vector world_n = vector_mult_matrix(obj_n, matrixTranspose(matrixInverse(cy.transform)), 1);

    world_n.w = 0;

    return normalize(world_n);
}
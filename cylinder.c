/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 21:14:35 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/08/18 13:45:26 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void cylinderInit(t_cy *cy, t_ambient ambient)
{
    cy->transform = get_matrix(cy->pos.x, cy->pos.y, cy->pos.z, 't');
    cy->material = materials(cy->rgb, ambient.ratio);
    cy->min = -1;
    cy->max = 2;
}

int check_cap (ray r, double t, double diameter)
{
    float x = r.start.x + t * r.dir.x;
    float z = r.start.z + t * r.dir.z;

    if (x * x + z * z <= diameter * diameter)
        return (1);
    return (0);
}

double intersect_caps(t_cy cy, ray r)
{
    if (r.dir.y < 0.001f)
        return (-1);
    
    double t0 = (cy.min - r.start.y) / r.dir.y;
    double t1 = (cy.max - r.start.y) / r.dir.y;

    if (check_cap(r, t0, cy.diameter))
        return (t0);
    else if (check_cap(r, t1, cy.diameter))
        return (t1);
    else 
        return (-1);
}

double cylinderIntersection(t_cy cy, ray r)
{
    double t0, t1;

    double a = r.dir.x * r.dir.x + r.dir.z * r.dir.z;
    
    if (a < 0.001f)
        return (-1);
    
    double b = 2 * r.start.x * r.dir.x + 2 * r.start.z * r.dir.z;
    double c = r.start.x * r.start.x + r.start.z * r.start.z - cy.diameter * cy.diameter;

    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return (-1);
    else
    {
        t0 = (-b - sqrt(discriminant)) / (2 * a);
        t1 = (-b + sqrt(discriminant)) / (2 * a);

        if(t0 > t1)
            t0 = t1;

        double y0 = r.start.y + t0 * r.dir.y;
        double y1 = r.start.y + t1 * r.dir.y;
        if (t0 > 0.001f && cy.min < y0 && y0 < cy.max)
            return (t0);
        else if (t1 > 0.001f && cy.min < y1 && y1 < cy.max)
            return (t1);
        else return (-1);
    }
}

double cylinder_caps_intersect(t_cy cy, ray r)
{
    ray r2;

    r2 = transform(r, cy.transform, -1);

    double t0 = cylinderIntersection(cy, r2);
    // double t1 = intersect_caps(cy, r2);

    // if (t0 == -1 && t1 == -1)
    //     return (-1);
    // if (t0 == -1)
    //     return (t1);
    // if (t1 == -1)
    //     return (t0);
    // if (t0 > t1)
    //     t0 = t1;
    return (t0);
}

t_vector normal_at_cylinder(t_cy cy, t_vector p)
{
    t_vector obj_p = vector_mult_matrix(p, cy.transform, -1);
    t_vector obj_n;
    double dist = p.x * p.x + p.z * p.z;
    if (dist < 1 && p.y >= cy.max - EPSILON)
        obj_n = vectorInit(0, 1, 0, 0);
    else if (dist < 1 && p.y <= cy.min + EPSILON)
        obj_n = vectorInit(0, -1, 0, 0);
    else 
        obj_n = vectorInit(obj_p.x, 0, obj_p.z, 0);
    t_vector world_n = vector_mult_matrix(obj_n, matrixTranspose(matrixInverse(cy.transform)), 1);

    world_n.w = 0;

    return normalize(world_n);
}
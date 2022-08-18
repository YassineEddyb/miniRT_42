/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 21:52:36 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/08/16 18:13:23 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// substruct tow vectors
t_vector vectorSub(t_vector v1, t_vector v2)
{
	t_vector result = {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w};
	return result;
}

// get the dot product of tow vectors
double vectorDot(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

// scale a vector with a number
t_vector vectorScale(t_vector v, double t)
{
    t_vector result = {v.x * t, v.y * t, v.z * t, v.w};
    return result;
}

// add tow vectors
t_vector vectorAdd(t_vector v1, t_vector v2)
{
        t_vector result = {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w};
        return result;
}

// normalize the vector 
t_vector normalize(t_vector v)
{
	double len = magnitude(v);
	t_vector result = {v.x / len, v.y / len, v.z / len, v.w};
	return result;
}

// get the length of a vector
double magnitude(t_vector v)
{
	return sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

// init vector
t_vector vectorInit(double x, double y, double z, double w)
{
	t_vector v;

	v.x = x;
	v.y = y;
	v.z = z;
	v.w = w;

	return (v);
}

// get the cross product of two vectors
t_vector vectorCross(t_vector a, t_vector b)
{
	t_vector res = {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x, 0};
	return res;
}
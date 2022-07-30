/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 21:52:36 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/07/30 14:34:14 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// substruct tow vectors
vector vectorSub(vector v1, vector v2)
{
	vector result = {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w};
	return result;
}

// get the dot product of tow vectors
float vectorDot(vector v1, vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

// scale a vector with a number
vector vectorScale(vector v, float t)
{
    vector result = {v.x * t, v.y * t, v.z * t, v.w};
    return result;
}

// add tow vectors
vector vectorAdd(vector v1, vector v2)
{
        vector result = {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w};
        return result;
}

// normalize the vector 
vector normalize(vector v)
{
	float len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	vector result = {v.x / len, v.y / len, v.z / len, v.w};
	return result;
}

// init vector
vector vectorInit(float x, float y, float z, float w)
{
	vector v;

	v.x = x;
	v.y = y;
	v.z = z;
	v.w = w;

	return (v);
}

// get the cross product of two vectors
vector vectorCross(vector a, vector b)
{
	vector res = {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x, 0};
	return res;
}
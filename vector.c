/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 21:52:36 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/07/27 11:59:50 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

vector vectorSub(vector v1, vector v2)
{
	vector result = {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w};
	return result;
}

float vectorDot(vector v1, vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

vector vectorScale(vector v, float t)
{
    vector result = {v.x * t, v.y * t, v.z * t, v.w};
    return result;
}

vector vectorAdd(vector v1, vector v2)
{
        vector result = {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w};
        return result;
}

vector normalize(vector v)
{
	float len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	vector result = {v.x / len, v.y / len, v.z / len, v.w};
	return result;
}

vector vectorInit(float x, float y, float z, float w)
{
	vector v;

	v.x = x;
	v.y = y;
	v.z = z;
	v.w = w;

	return (v);
}

vector vectorCross(vector a, vector b)
{
	vector res = {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x, 0};
	return res;
}
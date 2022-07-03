/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 21:52:36 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/07/03 23:29:29 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

vector vectorSub(vector *v1, vector *v2)
{
	vector result = {v1->x - v2->x, v1->y - v2->y, v1->z - v2->z };
	return result;
}

float vectorDot(vector *v1, vector *v2)
{
	return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}

vector vectorScale(float c, vector v)
{
        vector result = {v.x * c, v.y * c, v.z * c };
        return result;
}

vector vectorAdd(vector v1, vector v2)
{
        vector result = {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
        return result;
}

vector normalize(vector v)
{
	float len = sqrt(v.x * v.x + v.y* v.y + v.z* v.z);
	vector result = {v.x / len, v.y / len, v.z / len};
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
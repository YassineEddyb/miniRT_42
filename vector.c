/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 21:52:36 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/07/01 13:20:31 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* Subtract two vectors and return the resulting vector */
vector vectorSub(vector *v1, vector *v2)
{
	vector result = {v1->x - v2->x, v1->y - v2->y, v1->z - v2->z };
	return result;
}

/* Multiply two vectors and return the resulting scalar (dot product) */
float vectorDot(vector *v1, vector *v2)
{
	return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}

/* Calculate Vector x Scalar and return resulting Vector*/
vector vectorScale(float c, vector v)
{
        vector result = {v.x * c, v.y * c, v.z * c };
        return result;
}

/* Add two vectors and return the resulting vector */
vector vectorAdd(vector v1, vector v2)
{
        vector result = {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
        return result;
}

// get a vector with length 1
vector normalize(vector v)
{
	float len = sqrt(v.x * v.x + v.y* v.y + v.z* v.z);
	vector result = {v.x / len, v.y / len, v.z / len};
	return result;
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

vector vectorInit(float x, float y, float z)
{
	vector v;
	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}
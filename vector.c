/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 21:52:36 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/08/31 11:50:04 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// substruct tow vectors
t_vector	vector_sub(t_vector v1, t_vector v2)
{
	t_vector	result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	result.w = v1.w - v2.w;
	return (result);
}

// get the dot product of tow vectors
double	vector_dot(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

// scale a vector with a number
t_vector	vector_scale(t_vector v, double t)
{
	t_vector	result;

	result.x = v.x * t;
	result.y = v.y * t;
	result.z = v.z * t;
	result.w = v.w;
	return (result);
}

// add tow vectors
t_vector	vector_add(t_vector v1, t_vector v2)
{
	t_vector	result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	result.w = v1.w;
	return (result);
}

// normalize the vector 
t_vector	normalize(t_vector v)
{
	double		len;
	t_vector	result;

	len = magnitude(v);
	result.x = v.x / len;
	result.y = v.y / len;
	result.z = v.z / len;
	result.w = v.w;
	return (result);
}

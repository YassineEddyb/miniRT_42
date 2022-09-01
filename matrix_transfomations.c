/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transfomations.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 11:06:50 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/08/31 11:12:11 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// translate a vector by a matrix
t_vector	translate(t_vector v, t_vector translator, int type)
{
	t_matrix	m1;
	t_matrix	m2;
	t_matrix	m3;
	t_vector	res;

	m1 = matrix_create(4, 4);
	m2 = matrix_create(4, 1);
	m1 = get_matrix(translator.x, translator.y, translator.z, 't');
	m2.m[0][0] = v.x;
	m2.m[1][0] = v.y;
	m2.m[2][0] = v.z;
	m2.m[3][0] = v.w;
	if (type == -1)
		m3 = matrix_mult(matrix_inverse(m1), m2);
	else
		m3 = matrix_mult(m1, m2);
	res = vector_init(m3.m[0][0], m3.m[1][0], m3.m[2][0], m3.m[3][0]);
	return (res);
}

// scale a vector by a matrix
t_vector	scale(t_vector v, t_vector scaler, int type)
{
	t_matrix	m1;
	t_matrix	m2;
	t_matrix	m3;
	t_vector	res;

	m1 = matrix_create(4, 4);
	m2 = matrix_create(4, 1);
	m1 = get_matrix(scaler.x, scaler.y, scaler.z, 's');
	m2.m[0][0] = v.x;
	m2.m[1][0] = v.y;
	m2.m[2][0] = v.z;
	m2.m[3][0] = v.w;
	if (type == -1)
		m3 = matrix_mult(matrix_inverse(m1), m2);
	else
		m3 = matrix_mult(m1, m2);
	res = vector_init(m3.m[0][0], m3.m[1][0], m3.m[2][0], m3.m[3][0]);
	return (res);
}

// rotate a vector by a matrix
t_vector	rotate(t_vector v, double r, char axis)
{
	t_matrix	m1;
	t_matrix	m2;
	t_matrix	m3;
	t_vector	res;

	m1 = matrix_create(4, 4);
	m2 = matrix_create(4, 1);
	get_rotation_matrix(r, axis);
	m2.m[0][0] = v.x;
	m2.m[1][0] = v.y;
	m2.m[2][0] = v.z;
	m2.m[3][0] = v.w;
	m3 = matrix_mult(m1, m2);
	res = vector_init(m3.m[0][0], m3.m[1][0], m3.m[2][0], m3.m[3][0]);
	return (res);
}

// multiplu a vector by a matrix
t_vector	vector_mult_matrix(t_vector v, t_matrix m, int type)
{
	t_matrix	m2;
	t_matrix	m3;
	t_vector	res;

	m2 = matrix_create(4, 1);
	m2.m[0][0] = v.x;
	m2.m[1][0] = v.y;
	m2.m[2][0] = v.z;
	m2.m[3][0] = v.w;
	if (type == -1)
		m3 = matrix_mult(matrix_inverse(m), m2);
	else
		m3 = matrix_mult(m, m2);
	res = vector_init(m3.m[0][0], m3.m[1][0], m3.m[2][0], m3.m[3][0]);
	return (res);
}

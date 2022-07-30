/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transfomations.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 11:06:50 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/07/30 14:40:57 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// translate a vector by a matrix
vector translate(vector v, vector translator, int type)
{
    matrix m1;
    matrix m2;
    matrix m3;
    vector res;

    m1 = matrixCreate(4, 4);
    m2 = matrixCreate(4, 1);

    m1 = get_matrix(translator, 't');

    m2.m[0][0] = v.x;
    m2.m[1][0] = v.y;
    m2.m[2][0] = v.z;
    m2.m[3][0] = v.w;

    if (type == -1)
        m3 = matrixMult(matrixInverse(m1), m2);
    else m3 = matrixMult(m1, m2);
    res = vectorInit(m3.m[0][0], m3.m[1][0], m3.m[2][0], m3.m[3][0]);
    return (res);
}

// scale a vector by a matrix
vector scale(vector v, vector scaler, int type)
{
    matrix m1;
    matrix m2;
    matrix m3;
    vector res;

    m1 = matrixCreate(4, 4);
    m2 = matrixCreate(4, 1);

    m1 = get_matrix(scaler, 's');

    m2.m[0][0] = v.x;
    m2.m[1][0] = v.y;
    m2.m[2][0] = v.z;
    m2.m[3][0] = v.w;

    if (type == -1)
        m3 = matrixMult(matrixInverse(m1), m2);
    else m3 = matrixMult(m1, m2);
    res = vectorInit(m3.m[0][0], m3.m[1][0], m3.m[2][0], m3.m[3][0]);
    return (res);
}

// rotate a vector by a matrix
vector rotate(vector v, float r, char axis)
{
    matrix m1;
    matrix m2;
    matrix m3;
    vector res;

    m1 = matrixCreate(4, 4);
    m2 = matrixCreate(4, 1);

    get_rotation_matrix(r, axis);

    m2.m[0][0] = v.x;
    m2.m[1][0] = v.y;
    m2.m[2][0] = v.z;
    m2.m[3][0] = v.w;

    m3 = matrixMult(m1, m2);
    res = vectorInit(m3.m[0][0], m3.m[1][0], m3.m[2][0], m3.m[3][0]);
    return (res);
}

// multiplu a vector by a matrix
vector vector_mult_matrix (vector v, matrix m, int type)
{
    matrix m2;
    matrix m3;
    vector res;

    m2 = matrixCreate(4, 1);

    m2.m[0][0] = v.x;
    m2.m[1][0] = v.y;
    m2.m[2][0] = v.z;
    m2.m[3][0] = v.w;

    if (type == -1)
        m3 = matrixMult(matrixInverse(m), m2);
    else m3 = matrixMult(m, m2);
    res = vectorInit(m3.m[0][0], m3.m[1][0], m3.m[2][0], m3.m[3][0]);
    return (res);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transfomations.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 11:06:50 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/07/25 13:49:30 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

vector translate(vector v, vector translator, int type)
{
    matrix m1;
    matrix m2;
    matrix m3;
    vector res;

    m1 = matrixCreate(4, 4);
    m2 = matrixCreate(4, 1);

    m1.m[0][0] = 1;
    m1.m[1][1] = 1;
    m1.m[2][2] = 1;
    m1.m[3][3] = 1;
    m1.m[0][3] = translator.x;
    m1.m[1][3] = translator.y;
    m1.m[2][3] = translator.z;

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

vector scale(vector v, vector scaler, int type)
{
    matrix m1;
    matrix m2;
    matrix m3;
    vector res;

    m1 = matrixCreate(4, 4);
    m2 = matrixCreate(4, 1);

    m1.m[0][0] = scaler.x;
    m1.m[1][1] = scaler.y;
    m1.m[2][2] = scaler.z;
    m1.m[3][3] = 1;

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

vector rotate_x(vector v, float r)
{
    matrix m1;
    matrix m2;
    matrix m3;
    vector res;

    m1 = matrixCreate(4, 4);
    m2 = matrixCreate(4, 1);

    m1.m[0][0] = 1;
    m1.m[1][1] = cos(r);
    m1.m[1][2] = -sin(r);
    m1.m[2][2] = cos(r);
    m1.m[2][1] = sin(r);
    m1.m[3][3] = 1;

    m2.m[0][0] = v.x;
    m2.m[1][0] = v.y;
    m2.m[2][0] = v.z;
    m2.m[3][0] = v.w;

    m3 = matrixMult(m1, m2);
    res = vectorInit(m3.m[0][0], m3.m[1][0], m3.m[2][0], m3.m[3][0]);
    return (res);
}

vector rotate_y(vector v, float r)
{
    matrix m1;
    matrix m2;
    matrix m3;
    vector res;

    m1 = matrixCreate(4, 4);
    m2 = matrixCreate(4, 1);

    m1.m[0][0] = cos(r);
    m1.m[0][2] = sin(r);
    m1.m[1][1] = 1;
    m1.m[2][0] = -sin(r);
    m1.m[2][2] = cos(r);
    m1.m[3][3] = 1;

    m2.m[0][0] = v.x;
    m2.m[1][0] = v.y;
    m2.m[2][0] = v.z;
    m2.m[3][0] = v.w;

    m3 = matrixMult(m1, m2);
    res = vectorInit(m3.m[0][0], m3.m[1][0], m3.m[2][0], m3.m[3][0]);
    return (res);
}

vector rotate_z(vector v, float r)
{
    matrix m1;
    matrix m2;
    matrix m3;
    vector res;

    m1 = matrixCreate(4, 4);
    m2 = matrixCreate(4, 1);

    m1.m[0][0] = cos(r);
    m1.m[0][1] = -sin(r);
    m1.m[1][0] = sin(r);
    m1.m[1][1] = cos(r);
    m1.m[2][2] = 1;
    m1.m[3][3] = 1;

    m2.m[0][0] = v.x;
    m2.m[1][0] = v.y;
    m2.m[2][0] = v.z;
    m2.m[3][0] = v.w;

    m3 = matrixMult(m1, m2);
    res = vectorInit(m3.m[0][0], m3.m[1][0], m3.m[2][0], m3.m[3][0]);
    return (res);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutrix_inits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 11:21:13 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/07/30 14:38:12 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// create a matrix
matrix matrixCreate(int rows, int cols)
{
   matrix matrix;
   int i;
   int j;
   float **arr;

   arr = malloc(rows * sizeof(float *));
   i = 0;
   while (i < rows)
   {
      arr[i] = malloc(cols * sizeof(float));
      i++;
   }

   matrix.rows = rows;
   matrix.cols = cols;
   i = -1;
   while(++i < rows)
   {
      j = -1;
      while(++j < cols)
         arr[i][j] = 0;
   }
   matrix.m = arr;
   return (matrix);
}

// get the matrix
matrix get_matrix(vector v, char type) {
    matrix m = matrixCreate(4, 4);

    if (type == 't') {
        m.m[0][0] = 1;
        m.m[1][1] = 1;
        m.m[2][2] = 1;
        m.m[3][3] = 1;
        m.m[0][3] = v.x;
        m.m[1][3] = v.y;
        m.m[2][3] = v.z;
    } else if (type == 's')
    {
        m.m[0][0] = v.x;
        m.m[1][1] = v.y;
        m.m[2][2] = v.z;
        m.m[3][3] = 1;
    } else {
        m.m[0][0] = 1;
        m.m[1][1] = 1;
        m.m[2][2] = 1;
        m.m[3][3] = 1;
    }

    return m;
}

// get the rotation matrix
matrix get_rotation_matrix(float r, int type)
{
    matrix m = matrixCreate(4, 4);

    if (type == 'x') {
        m.m[0][0] = 1;
        m.m[1][1] = cos(r);
        m.m[1][2] = -sin(r);
        m.m[2][2] = cos(r);
        m.m[2][1] = sin(r);
        m.m[3][3] = 1;
    } else if (type == 'y') {
        m.m[0][0] = cos(r);
        m.m[0][2] = sin(r);
        m.m[1][1] = 1;
        m.m[2][0] = -sin(r);
        m.m[2][2] = cos(r);
        m.m[3][3] = 1;
    } else if (type == 'z') {
        m.m[0][0] = cos(r);
        m.m[0][1] = -sin(r);
        m.m[1][0] = sin(r);
        m.m[1][1] = cos(r);
        m.m[2][2] = 1;
        m.m[3][3] = 1;
    }

    return m;
}
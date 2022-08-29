/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutrix_inits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 11:21:13 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/08/28 11:40:28 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// create a matrix
t_matrix matrix_create(int rows, int cols)
{
   t_matrix matrix;
   int i;
   int j;
   double **arr;

   arr = malloc(rows * sizeof(double *));
   i = 0;
   while (i < rows)
   {
      arr[i] = malloc(cols * sizeof(double));
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
t_matrix get_matrix(double x, double y, double z, char type)
{
    t_matrix m = matrix_create(4, 4);

    if (type == 't') {
        m.m[0][0] = 1;
        m.m[1][1] = 1;
        m.m[2][2] = 1;
        m.m[3][3] = 1;
        m.m[0][3] = x;
        m.m[1][3] = y;
        m.m[2][3] = z;
    } else if (type == 's')
    {
        m.m[0][0] = x;
        m.m[1][1] = y;
        m.m[2][2] = z;
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
t_matrix get_rotation_matrix(double r, int type)
{
    t_matrix m = matrix_create(4, 4);

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
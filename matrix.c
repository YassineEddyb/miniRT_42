/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 21:55:32 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/07/01 13:13:45 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

matrix matrixCreate(int rows, int cols)
{
   matrix matrix;
   int i;
   int j;
   float **arr;

   arr = malloc(cols * sizeof(float *));
   i = 0;
   while (i < cols)
   {
      arr[i] = malloc(rows * sizeof(float));
      i++;
   }

   matrix.rows = rows;
   matrix.cols = cols;
   i = -1;
   while(++i < cols)
   {
      j = -1;
      while(++j < rows)
         arr[i][j] = 0;
   }
   matrix.m = arr;
   return (matrix);
}

matrix matrixMult(matrix m1, matrix m2)
{
   int i;
   int j;
   int k;
   matrix result;

   result = matrixCreate(m1.rows, m1.cols);

   i = -1;
   while (++i < m1.rows)
   {
      j = -1;
      while (++j < m1.cols)
      {
         k = -1;
         while (++k < m1.rows)
            result.m[i][j] += m1.m[i][k] * m2.m[k][j];
      }
   }
   return (result);
}

matrix matrixTranspose(matrix m)
{
   int i;
   int j;
   matrix transpose;

   transpose = matrixCreate(m.rows, m.cols);

   i = -1;
   while (++i < m.rows)
   {
      j = -1;
      while (++j < m.cols)
         transpose.m[j][i] = m.m[i][j];
   }
   return (transpose);
}

void print_matrix(matrix m)
{
   int j;
   int i = 0;
   while(i < m.rows)
   {
      j = 0;
      while(j < m.cols)
      {
         printf("%f|", m.m[i][j]);
         j++;
      }
      printf("\n");
      i++;
   }
}

int main () {
   matrix m1;
   matrix m2;
   matrix m3;
   matrix m4;
   int i;
   int j;

   m1 = matrixCreate(4, 4);
   m2 = matrixCreate(4, 4);

   m1.m[0][0] = 1;
   m1.m[0][1] = 2;
   m1.m[0][2] = 3;
   m1.m[0][3] = 4;
   m1.m[1][0] = 5;
   m1.m[1][1] = 6;
   m1.m[1][2] = 7;
   m1.m[1][3] = 8;
   m1.m[2][0] = 9;
   m1.m[2][1] = 8;
   m1.m[2][2] = 7;
   m1.m[2][3] = 6;
   m1.m[3][0] = 5;
   m1.m[3][1] = 4;
   m1.m[3][2] = 3;
   m1.m[3][3] = 2;

   m2.m[0][0] = 1;
   m2.m[1][1] = 1;
   m2.m[2][2] = 1;
   m2.m[3][3] = 1;

   m3 = submatrix(m1, 1, 1);
   m4 = submatrix(m3, 0, 2);

   print_matrix(m1);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 21:55:32 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/07/03 13:28:29 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
   printf("\n");
}

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

matrix matrixMult(matrix m1, matrix m2)
{
   int i;
   int j;
   int k;
   matrix result;

   if (m1.cols != m2.rows)
      exit(1);
   result = matrixCreate(m1.rows, m2.cols);
   i = -1;
   while (++i < m1.rows)
   {
      j = -1;
      while (++j < m2.cols)
      {
         k = -1;
         while (++k < m1.cols)
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

matrix cofactor_matrix(matrix m)
{
   int i, j;
   matrix matrix;

   matrix = matrixCreate(m.rows, m.cols);

   i = 0;
   while(i < m.rows)
   {
      j = 0;
      while(j < m.cols)
      {
         matrix.m[i][j] = cofactor(matrixDeterminant(submatrix(m, i, j)), i, j);
         j++;
      }
      i++;
   }

   return (matrix);
}

matrix matrix_devide_by_det(matrix m, float det)
{
   int i;
   int j;
   matrix inverted;

   i = 0;
   inverted  = matrixCreate(m.rows, m.cols);
   while(i < m.rows)
   {
      j = 0;
      while(j < m.cols)
      {
         inverted.m[i][j] = m.m[i][j] / det;
         j++;
      }
      i++;
   }

   return(inverted);
}

matrix matrixInverse(matrix m)
{
   float det;
   matrix matrix;

   det = matrixDeterminant(m);

   if (det == 0)
      exit(1);
   
   matrix = cofactor_matrix(m);
   matrix = matrixTranspose(matrix);
   matrix = matrix_devide_by_det(matrix, det);

   return (matrix);
}
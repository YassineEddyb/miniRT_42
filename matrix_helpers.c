/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 13:13:01 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/07/01 13:17:47 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float determinant(matrix m)
{
   return (m.m[0][0] * m.m[1][1] - m.m[0][1] * m.m[1][0]);   
}


matrix submatrix(matrix m, int row, int col)
{
   int i;
   int j;
   int k;
   int n;
   matrix sub;

   sub = matrixCreate(m.rows - 1, m.cols - 1);
   i = -1;
   k = 0;
   while (++i < m.rows)
   {
      if (i == row)
         i++;
      j = -1;
      n = 0;
      while (++j < m.cols)
      {
         if (j != col)
         {
            sub.m[k][n] = m.m[i][j];
            n++;
         }
      }
      k++;
   }
   return (sub);
}

float minor(matrix m, int rwo, int col)
{
    return (determinant(submatrix(m, rwo, col)));
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 13:13:01 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/09/04 15:11:09 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/miniRT.h"

// get the determinant of a submatrix
double	determinant(t_matrix m)
{
	return (m.m[0][0] * m.m[1][1] - m.m[0][1] * m.m[1][0]);
}

// get the submatrix base on row and col
t_matrix	submatrix(t_matrix m, int row, int col)
{
	int			i;
	int			j;
	int			k;
	int			n;
	t_matrix	sub;

	sub = matrix_create(m.rows - 1, m.cols - 1);
	i = -1;
	k = 0;
	while (++i < m.rows)
	{
		if (i != row)
		{
			j = -1;
			n = -1;
			while (++j < m.cols)
			{
				if (j != col)
					sub.m[k][++n] = m.m[i][j];
			}
			k++;
		}
	}
	return (sub);
}

// get teh minor of a matrix
double	minor(t_matrix m, int row, int col)
{
	return (determinant(submatrix(m, row, col)));
}

// calculate the cofactor 
double	cofactor(double det, int row, int col)
{
	return (pow(-1, row + col) * det);
}

// get the determinant of a matrix
double	matrix_determinant(t_matrix m)
{
	int		i;
	double	det;

	if (m.rows == 2 && m.cols == 2)
		return (determinant(m));
	i = 0;
	det = 0;
	while (i < m.cols)
	{
		det += m.m[0][i] * cofactor(
				matrix_determinant(submatrix(m, 0, i)), 0, i);
		i++;
	}
	return (det);
}

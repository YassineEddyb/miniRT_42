/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 17:46:58 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/07/30 17:58:09 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

matrix view_transform(vector from, vector to, vector up)
{
    vector forward  = normalize(vectorSub(to, from));
    vector upn = normalize(up);
    vector left =  vectorCross(forward, upn);
    vector true_up = vectorCross(left, forward);

    matrix or = matrixCreate(4, 4);
    
    or.m[0][0] = left.x;
    or.m[0][1] = left.y;
    or.m[0][2] = left.z;
    or.m[1][0] = true_up.x;
    or.m[1][1] = true_up.x;
    or.m[1][2] = true_up.x;
    or.m[2][0] = -forward.x;
    or.m[2][1] = -forward.x;
    or.m[2][2] = -forward.x;
    or.m[3][3] = 1;

    matrix m = get_matrix(vectorInit(-from.x, -from.y, from.z, 1), 't');

    return matrixMult(or, m);
}
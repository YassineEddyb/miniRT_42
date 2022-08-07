/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 11:37:48 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/08/07 20:46:17 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// init colour
colour colourInit(double r, double g, double b)
{
    colour c;

    c.red = r;
    c.green = g;
    c.blue = b;

    return c;
}

colour stripe_at(vector point)
{
    if (((int)floor(point.x) + (int)floor(point.y) + (int)floor(point.z)) % 2 == 0)
        return colourInit(0.8, 0.8, 0.8);
    else
        return colourInit(0.2, 0.2, 0.2);
}


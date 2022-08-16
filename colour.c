/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 11:37:48 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/08/15 10:04:12 by yed-dyb          ###   ########.fr       */
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
    if ((int)(round(point.x) + round(point.y) + round(point.z)) % 2 == 0)
        return colourInit(0.1, 0.1, 0.1);
    else
        return colourInit(1, 1, 1);
}


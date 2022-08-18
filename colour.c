/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 11:37:48 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/08/16 18:40:33 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// init colour
t_RGB colourInit(double r, double g, double b)
{
    t_RGB c;

    c.red = r;
    c.green = g;
    c.blue = b;

    return c;
}

t_RGB stripe_at(t_vector point)
{
    if ((int)(round(point.x) + round(point.y) + round(point.z)) % 2 == 0)
        return colourInit(0.1, 0.1, 0.1);
    else
        return colourInit(1, 1, 1);
}


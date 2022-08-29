/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 11:37:48 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/08/28 14:37:42 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// init colour
t_RGB	colour_init(double r, double g, double b)
{
	t_RGB	c;

	c.red = r;
	c.green = g;
	c.blue = b;
	return (c);
}

// checker board color
t_RGB	stripe_at(t_vector point)
{
	if ((int)(round(point.x) + round(point.y) + round(point.z)) % 2 == 0)
		return (colour_init(0.1, 0.1, 0.1));
	else
		return (colour_init(1, 1, 1));
}

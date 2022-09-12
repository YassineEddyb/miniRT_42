/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 11:37:48 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/09/01 22:23:52 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/miniRT.h"

// init color
t_RGB	color_init(double r, double g, double b)
{
	t_RGB	c;

	c.red = r;
	c.green = g;
	c.blue = b;
	return (c);
}

t_RGB	mult_colors(t_RGB color1, t_RGB color2)
{
	t_RGB	color;

	color = color_init(color1.red * color2.red,
			color1.green * color2.green,
			color1.blue * color2.blue);
	return (color);
}

t_RGB	add_colors(t_RGB color1, t_RGB color2)
{
	t_RGB	color;

	color = color_init(color1.red + color2.red,
			color1.green + color2.green,
			color1.blue + color2.blue);
	return (color);
}

t_RGB	scale_colors(t_RGB color1, double scaler)
{
	t_RGB	color;

	color = color_init(color1.red * scaler,
			color1.green * scaler,
			color1.blue * scaler);
	return (color);
}

// checker board color
t_RGB	stripe_at(t_plane plane, t_vector point, char type)
{
	if ((int)(round(point.x) + round(point.y) + round(point.z)) % 2 == 0 && type == 'c')
		return (color_init(plane.rgb.red / 255,
				plane.rgb.green / 255, plane.rgb.blue / 255));
	if (((int)round(point.x) + (int)round(point.z)) % 2 == 0 && type == 'b')
		return (color_init(plane.rgb.red / 255,
				plane.rgb.green / 255, plane.rgb.blue / 255));
	if (plane.rgbcheck.red > -1)
		return (color_init(plane.rgbcheck.red / 255,
				plane.rgbcheck.green / 255, plane.rgbcheck.blue / 255));
	return (color_init(plane.rgb.red / 255,
			plane.rgb.green / 255, plane.rgb.blue / 255));
}

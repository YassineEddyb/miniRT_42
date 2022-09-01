/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 11:30:33 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/08/31 14:06:49 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// init light
void	lightInit(t_light *light)
{
	light->rgb.red = light->rgb.red / 255;
	light->rgb.green = light->rgb.green / 255;
	light->rgb.blue = light->rgb.blue / 255;	
}

// init ambient
void	ambientInit(t_ambient *ambient)
{
	ambient->rgb.red = ambient->rgb.red / 255;
	ambient->rgb.green = ambient->rgb.green / 255;
	ambient->rgb.blue = ambient->rgb.blue / 255;
}

t_RGB get_specular(t_light_data data, t_vector lightv)
{
	t_RGB specular;
	t_vector reflectv;
	double reflect_dot_eye;
	double factor;
	double light_specular;
	
	reflectv = reflect(vector_scale(lightv, -1), data.normalv);
	reflect_dot_eye = vector_dot(reflectv, data.eyev);

	if (reflect_dot_eye <= 0)
		specular = colour_init(0, 0, 0);
	else {
		double factor  = pow(reflect_dot_eye, data.m.shininess);
		double light_specular = data.m.specular * factor;
		specular = colour_init(data.l.rgb.red * light_specular, data.l.rgb.green * light_specular, data.l.rgb.blue * light_specular);
	}
}

// the the lighting color of an intersection pixel
t_RGB	lightning(t_light_data data, int in_shadow)
{
	t_RGB diffuse;
	t_RGB specular;
	t_RGB eff_color = colour_init(data.m.color.red * data.l.rgb.red * data.am.rgb.red, data.m.color.green * data.l.rgb.green * data.am.rgb.green, data.m.color.blue * data.l.rgb.blue * data.am.rgb.blue);
	t_vector lightv = normalize(vector_sub(data.l.pos, data.pos));
	t_RGB ambient = colour_init(eff_color.red * data.m.ambient, eff_color.green * data.m.ambient, eff_color.blue * data.m.ambient);
	double light_dot_n = vector_dot(lightv, data.normalv);

	if (light_dot_n < 0 || in_shadow)
	{
		diffuse = colour_init(0, 0, 0);
		specular = colour_init(0, 0, 0);
	}
	else
	{
		double light_diffuse = light_dot_n * data.l.ratio;
		diffuse = colour_init(eff_color.red * light_diffuse, eff_color.green *  light_diffuse, eff_color.blue * light_diffuse);
	}
	return colour_init(ambient.red + diffuse.red + specular.red, ambient.green + diffuse.green + specular.green, ambient.blue + diffuse.blue + specular.blue);
}
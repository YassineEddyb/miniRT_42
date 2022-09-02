/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 11:30:33 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/09/02 21:24:37 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// init light
void	light_init(t_light *light)
{
	light->pos.x += FLT_EPSILON;
	light->pos.y += FLT_EPSILON;
	light->pos.z += FLT_EPSILON;
	light->rgb.red = light->rgb.red / 255;
	light->rgb.green = light->rgb.green / 255;
	light->rgb.blue = light->rgb.blue / 255;
}

// init ambient
void	ambient_init(t_ambient *ambient)
{
	ambient->rgb.red = ambient->rgb.red / 255;
	ambient->rgb.green = ambient->rgb.green / 255;
	ambient->rgb.blue = ambient->rgb.blue / 255;
}

t_RGB	get_specular(t_light_data data, t_comps comps, t_vector lightv)
{
	t_RGB		specular;
	t_vector	reflectv;
	double		reflect_dot_eye;
	double		factor;
	double		light_specular;

	reflectv = reflect(vector_scale(lightv, -1), comps.normalv);
	reflect_dot_eye = vector_dot(reflectv, comps.eyev);
	if (reflect_dot_eye <= 0)
		specular = color_init(0, 0, 0);
	else
	{
		factor = pow(reflect_dot_eye, data.m.shininess);
		light_specular = data.m.specular * factor;
		specular = color_init(data.l.rgb.red * light_specular,
				data.l.rgb.green * light_specular,
				data.l.rgb.blue * light_specular);
	}
	return (specular);
}

// the the lighting color of an intersection pixel
t_RGB	lightning(t_light_data data, t_comps comps, int in_shadow)
{
	t_phong	phong;

	phong.eff_color = mult_colors(mult_colors(
				data.m.color, data.l.rgb), data.am.rgb);
	phong.lightv = normalize(vector_sub(data.l.pos, data.pos));
	phong.ambient = scale_colors(phong.eff_color, data.m.ambient);
	phong.light_dot_n = vector_dot(phong.lightv, comps.normalv);
	if (phong.light_dot_n < 0 || in_shadow)
	{
		phong.diffuse = color_init(0, 0, 0);
		phong.specular = color_init(0, 0, 0);
	}
	else
	{
		phong.light_diffuse = phong.light_dot_n * data.l.ratio;
		phong.diffuse = scale_colors(phong.eff_color, phong.light_diffuse);
		phong.specular = get_specular(data, comps, phong.lightv);
	}
	return (add_colors(add_colors(
				phong.ambient, phong.diffuse), phong.specular));
}

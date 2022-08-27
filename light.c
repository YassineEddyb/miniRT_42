/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 11:30:33 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/08/26 11:49:34 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// int light
void lightInit(t_light *light)
{
    light->rgb.red = light->rgb.red / 255;
    light->rgb.green = light->rgb.green / 255;
    light->rgb.blue = light->rgb.blue / 255;
}

void ambientInit(t_ambient *ambient)
{
    ambient->rgb.red = ambient->rgb.red / 255;
    ambient->rgb.green = ambient->rgb.green / 255;
    ambient->rgb.blue = ambient->rgb.blue / 255;
}

// the the lighting color of an intersection pixel
t_RGB lightning(t_ambient am, t_material m, t_light l, t_vector pos, t_vector v, t_vector n, int in_shadow)
{
    t_RGB diffuse;
    t_RGB specular;
    t_RGB eff_color = colourInit(m.color.red * l.rgb.red * am.rgb.red, m.color.green * l.rgb.green * am.rgb.green, m.color.blue * l.rgb.blue * am.rgb.blue);
    t_vector lightv = normalize(vectorSub(l.pos, pos));
    t_RGB ambient = colourInit(eff_color.red * m.ambient, eff_color.green * m.ambient, eff_color.blue * m.ambient);
    double light_dot_n = vectorDot(lightv, n);

    if (light_dot_n < 0 || in_shadow)
    {
        diffuse = colourInit(0, 0, 0);
        specular = colourInit(0, 0, 0);
    } else {
        double light_diffuse = light_dot_n * l.ratio;
        diffuse = colourInit(eff_color.red * light_diffuse, eff_color.green *  light_diffuse, eff_color.blue * light_diffuse);

        t_vector reflectv = reflect(vectorScale(lightv, -1), n);
        double reflect_dot_eye = vectorDot(reflectv, v);

        if (reflect_dot_eye <= 0)
            specular = colourInit(0, 0, 0);
        else {
            double factor  = pow(reflect_dot_eye, m.shininess);
            double light_specular = m.specular * factor;
            specular = colourInit(l.rgb.red * light_specular, l.rgb.green * light_specular, l.rgb.blue * light_specular);
        }
    }
    
    return colourInit(ambient.red + diffuse.red + specular.red, ambient.green + diffuse.green + specular.green, ambient.blue + diffuse.blue + specular.blue);
}
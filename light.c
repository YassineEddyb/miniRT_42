/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 11:30:33 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/08/07 20:37:52 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// int light
light lightInit(vector pos, colour intensity)
{
    light l;

    l.pos = pos;
    l.intensity = intensity;

    return l;
}

// the the lighting color of an intersection pixel
colour lightning(material m, light l, vector pos, vector v, vector n, int in_shadow)
{
    colour diffuse;
    colour specular;
    colour eff_color = colourInit(m.color.red * l.intensity.red, m.color.green * l.intensity.green, m.color.blue * l.intensity.blue);
    vector lightv = normalize(vectorSub(l.pos, pos));
    colour ambient = colourInit(eff_color.red * m.ambient, eff_color.green * m.ambient, eff_color.blue * m.ambient);
    double light_dot_n = vectorDot(lightv, n);

    if (light_dot_n < 0 || in_shadow)
    {
        diffuse = colourInit(0, 0, 0);
        specular = colourInit(0, 0, 0);
    } else {
        double light_diffuse = light_dot_n * m.diffuse;
        diffuse = colourInit(eff_color.red * light_diffuse, eff_color.green * light_diffuse, eff_color.blue * light_diffuse);

        vector reflectv = reflect(vectorScale(lightv, -1), n);
        double reflect_dot_eye = vectorDot(reflectv, v);

        if (reflect_dot_eye <= 0)
        {
                specular = colourInit(0, 0, 0);
        } else {
                double factor  = pow(reflect_dot_eye, m.shininess);
                double light_specular = m.specular * factor;
                specular = colourInit(l.intensity.red * light_specular, l.intensity.green * light_specular, l.intensity.blue * light_specular);
        }
    }
    
    return colourInit(ambient.red + diffuse.red + specular.red, ambient.green + diffuse.green + specular.green, ambient.blue + diffuse.blue + specular.blue);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 11:54:53 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/08/21 10:03:05 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// materail init
t_material materials(t_RGB color, double ratio)
{
    t_material m;

    // printf("%s\n", ratio);
    m.color = colourInit(color.red / 255, color.green / 255, color.blue / 255);
	m.ambient = ratio;
    // m.diffuse = 0.2;
    m.specular = 0.2;
    m.shininess = 100;

    return m;
}
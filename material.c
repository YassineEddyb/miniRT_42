/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 11:54:53 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/08/20 14:53:38 by yed-dyb          ###   ########.fr       */
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
    // m.diffuse = diffuse;
    m.specular = 0.4;
    m.shininess = 20;

    return m;
}
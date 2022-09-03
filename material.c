/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 11:54:53 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/09/03 11:10:08 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// materail init
t_material	materials(t_RGB color, double ratio)
{
	t_material	m;

	m.color = color_init(color.red / 255, color.green / 255, color.blue / 255);
	m.ambient = ratio;
	m.specular = 0.7;
	m.shininess = 200;
	return (m);
}

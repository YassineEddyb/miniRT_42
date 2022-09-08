/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 11:54:53 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/09/08 11:49:20 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/miniRT.h"

// materail init
t_material	materials(t_RGB color, double ratio, double shininess, double reflective)
{
	t_material	m;

	m.color = color_init(color.red / 255, color.green / 255, color.blue / 255);
	m.ambient = ratio;
	m.shininess = shininess;
	m.reflective = reflective;
	return (m);
}

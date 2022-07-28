/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 11:54:53 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/07/27 12:05:36 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

material materials()
{
    material m;

    m.color = colourInit(1, 1, 1);
	m.ambient = 0.1;
    m.diffuse = 0.9;
    m.specular = 0.9;
    m.shininess = 200.0;

    return m;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_leaks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 17:26:43 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/09/04 18:07:44 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/miniRT.h"

void	free_matrix(t_matrix m)
{
	int	i;

	i = -1;
	while (++i < m.rows)
		free(m.m[i]);
	free(m.m);
}

void	free_objects(t_world *world)
{
	int	i;

	i = 0;
	while (world->sphere[i])
	{
		free_matrix(world->sphere[i]->transform);
		free_matrix(world->sphere[i]->inverted_transform);
		i++;
	}
	i = 0;
	while (world->plane[i])
	{
		free_matrix(world->plane[i]->transform);
		free_matrix(world->plane[i]->inverted_transform);
		i++;
	}
	i = 0;
	while (world->cy[i])
	{
		free_matrix(world->cy[i]->transform);
		free_matrix(world->cy[i]->inverted_transform);
		i++;
	}
	free_matrix(world->camera[0]->transform);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <ael-bach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 23:28:32 by ael-bach          #+#    #+#             */
/*   Updated: 2022/07/25 14:59:07 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/parser.h"

/***************************/
t_index	*count_index_part2(char **tmp, t_index *index)
{
	int	len;

	len = 2;
	if (ft_strlen(tmp[0]) > 2)
		len = ft_strlen(tmp[0]);
	if (!ft_strncmp(tmp[0], "sp", len))
	{
		index->sp  += 1;
		return (index);
	}
	if (!ft_strncmp(tmp[0], "pl", len))
	{
		index->pl += 1;
		return (index);
	}
	if (!ft_strncmp(tmp[0], "cy", len))
	{
		index->cy += 1;
		return (index);
	}
	return (NULL);	
}
t_index	*fill_index(void)
{
	t_index	*index;

	index = malloc(sizeof(t_index));
	if (!index)
		error("ERROR: ALLOCATION !!");
	index->A = 0;
	index->L = 0;
	index->C = 0;
	index->sp = 0;
	index->pl = 0;
	index->cy = 0;
	return (index);
}

t_index	*count_index(char **file)
{
	int		i;
	char	**tmp;
	t_index	*index;
	t_index	tmpindex;

	index = fill_index();
	i = -1;
	while (file[++i])
	{
		tmpindex = *index;
		tmp = ft_split_spaces(file[i], ' ');
		if (!ft_strncmp(tmp[0], "A", ft_strlen(tmp[0])))
			index->A++;
		else if (!ft_strncmp(tmp[0], "C", ft_strlen(tmp[0])))
			index->C++;
		else if (!ft_strncmp(tmp[0], "L", ft_strlen(tmp[0])))
			index->L++;
		else if (count_index_part2(tmp, &tmpindex))
			index = count_index_part2(tmp, index);
		else
			error("ERROR IN FILE");
		free_two_arr(tmp);
	}
	return (index);
}

t_data	*allocate_data(t_index *index)
{
	t_data	*data;

	data = malloc (sizeof(t_data));
	if (!data)
		error("ERROR: ALLOCATION !!");
	data->A = malloc (sizeof(t_ambient*) * index->A);
	if (!data->A)
		error("ERROR: ALLOCATION !!");
	data->C = malloc (sizeof(t_camera*) * index->C);
	if (!data->C)
		error("ERROR: ALLOCATION !!");
	data->L = malloc (sizeof(t_light*) * index->L);
	if (!data->L)
		error("ERROR: ALLOCATION !!");
	data->sp = malloc (sizeof(t_sphere*) * index->sp);
	if (!data->sp)
		error("ERROR: ALLOCATION !!");
	data->pl = malloc (sizeof(t_plane*) * index->pl);
	if (!data->pl)
		error("ERROR: ALLOCATION !!");
	data->cy = malloc (sizeof(t_cy*) * index->cy);
	if (!data->cy)
		error("ERROR: ALLOCATION !!");
	return (data);	
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 23:28:32 by ael-bach          #+#    #+#             */
/*   Updated: 2022/09/11 13:40:49 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/parser.h"

t_index	*count_index_part2(char **tmp, t_index *index)
{
	int	len;

	len = 2;
	if (ft_strlen(tmp[0]) > 2)
		len = ft_strlen(tmp[0]);
	if (!ft_strncmp(tmp[0], "sp", len))
	{
		index->sp += 1;
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
	if (!ft_strncmp(tmp[0], "cb", len))
	{
		index->cb += 1;
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
	index->a = 0;
	index->l = 0;
	index->c = 0;
	index->sp = 0;
	index->pl = 0;
	index->cy = 0;
	index->cb = 0;
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
			index->a++;
		else if (!ft_strncmp(tmp[0], "C", ft_strlen(tmp[0])))
			index->c++;
		else if (!ft_strncmp(tmp[0], "L", ft_strlen(tmp[0])))
			index->l++;
		else if (count_index_part2(tmp, &tmpindex))
			index = count_index_part2(tmp, index);
		else if (tmp[0][0] == '#')
			continue;
		else
			error("ERROR IN FILE");
		free_two_arr(tmp);
	}
	return (index);
}

t_world	*allocate_data(t_index *index)
{
	t_world	*data;

	data = malloc (sizeof(t_world));
	if (!data)
		error("ERROR: ALLOCATION !!");
	data->ambient = malloc (sizeof(t_ambient *) * (index->a + 1));
	if (!data->ambient)
		error("ERROR: ALLOCATION !!");
	data->camera = malloc (sizeof(t_camera *) * (index->c + 1));
	if (!data->camera)
		error("ERROR: ALLOCATION !!");
	data->light = malloc (sizeof(t_light *) * (index->l + 1));
	if (!data->light)
		error("ERROR: ALLOCATION !!");
	data->sphere = malloc (sizeof(t_sphere *) * (index->sp + 1));
	if (!data->sphere)
		error("ERROR: ALLOCATION !!");
	data->plane = malloc (sizeof(t_plane *) * (index->pl + 1));
	if (!data->plane)
		error("ERROR: ALLOCATION !!");
	data->cy = malloc (sizeof(t_cy *) * (index->cy + 1));
	if (!data->cy)
		error("ERROR: ALLOCATION !!");
	data->cube = malloc (sizeof(t_cube *) * (index->cb + 1));
	if (!data->cube)
		error("ERROR: ALLOCATION !!");
	return (data);
}

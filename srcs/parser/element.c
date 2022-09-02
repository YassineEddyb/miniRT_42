/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <ael-bach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 12:35:10 by ael-bach          #+#    #+#             */
/*   Updated: 2022/09/02 12:23:32 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/parser.h"

void	error(char *str)
{
	printf("%s\n", str);
	exit (1);
}

void	free_two_arr(char **arr)
{
	int		i;

	i = 0;
	while (arr[i++])
		free (arr[i]);
	free (arr);
}

t_world	*identifier(char **tmp, t_world *data, t_index *index)
{
	int	len;

	len = 2;
	if (ft_strlen(tmp[0]) > 2)
		len = ft_strlen(tmp[0]);
	if (!ft_strncmp(tmp[0], "sp", len))
	{
		data->sphere[index->sp++] = sphere(tmp);
		return (data);
	}
	if (!ft_strncmp(tmp[0], "pl", len))
	{
		data->plane[index->pl++] = plane(tmp);
		return (data);
	}
	if (!ft_strncmp(tmp[0], "cy", len))
	{
		data->cy[index->cy++] = cylinder(tmp);
		return (data);
	}
	return (NULL);
}

t_world	*fi2(char **file, t_index *index, t_world *data, t_index tmpindex)
{
	int		i;
	char	**tmp;

	i = -1;
	while (file[++i])
	{
		tmpindex = *index;
		tmp = ft_split_spaces(file[i], ' ');
		if (!ft_strncmp(tmp[0], "A", ft_strlen(tmp[0])))
			data->ambient[index->a++] = ambient_light(tmp);
		else if (!ft_strncmp(tmp[0], "C", ft_strlen(tmp[0])))
			data->camera[index->c++] = camera(tmp);
		else if (!ft_strncmp(tmp[0], "L", ft_strlen(tmp[0])))
			data->light[index->l++] = light(tmp);
		else if (identifier(tmp, data, &tmpindex))
			data = identifier(tmp, data, index);
		else
			error("ERROR IN FILE");
		free_two_arr(tmp);
	}
	return (data);
}

t_world	*check_and_fill(char **file)
{
	char		**tmp;
	t_world		*data;
	t_index		*index;
	t_index		tmpindex;

	if (!file)
		error("ERROR : EMPTY FILE");
	index = count_index(file);
	data = allocate_data(index);
	free (index);
	index = fill_index();
	data = fi2(file, index, data, tmpindex);
	data->ambient[index->a] = NULL;
	data->camera[index->c] = NULL;
	data->light[index->l] = NULL;
	data->cy[index->cy] = NULL;
	data->plane[index->pl] = NULL;
	data->sphere[index->sp] = NULL;
	if (index->a != 1 || index->c != 1 || index->l != 1)
		error("ERROR : IN FILE");
	free (index);
	free_two_arr(file);
	return (data);
}

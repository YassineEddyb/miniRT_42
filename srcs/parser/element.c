/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <ael-bach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 12:35:10 by ael-bach          #+#    #+#             */
/*   Updated: 2022/07/25 14:58:57 by ael-bach         ###   ########.fr       */
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


t_data	*identifier(char **tmp, t_data *data, t_index *index)
{
	int	len;

	len = 2;
	if (ft_strlen(tmp[0]) > 2)
		len = ft_strlen(tmp[0]);
	if (!ft_strncmp(tmp[0], "sp", len))
	{
		data->sp[index->sp++] = sphere(tmp);
		return (data);
	}
	if (!ft_strncmp(tmp[0], "pl", len))
	{
		data->pl[index->pl++] = plane(tmp);
		return (data);
	}
	if (!ft_strncmp(tmp[0], "cy", len))
	{
		data->cy[index->cy++] = cylinder(tmp);
		return (data);
	}
	return (NULL);	
}

t_data	*check_and_fill(char **file)
{
	int		i;
	char	**tmp;
	t_data	*data;
	t_index	*index;
	t_index	tmpindex;

	i = -1;
	if (!file)
		error("ERROR : EMPTY FILE");
	index = count_index(file);
	data = allocate_data(index);
	free (index);
	index = fill_index();
	while (file[++i])
	{
		tmpindex = *index;
		tmp = ft_split_spaces(file[i], ' ');
		if (!ft_strncmp(tmp[0], "A", ft_strlen(tmp[0])))
			data->A[index->A++] = ambient_light(tmp);
		else if (!ft_strncmp(tmp[0], "C", ft_strlen(tmp[0])))
			data->C[index->C++] = camera(tmp);
		else if (!ft_strncmp(tmp[0], "L", ft_strlen(tmp[0])))
			data->L[index->L++] = light(tmp);
		else if (identifier(tmp,data, &tmpindex))
			data = identifier(tmp,data, index);
		else
			error("ERROR IN FILE");
		free_two_arr(tmp);
	}
	return (data);
}
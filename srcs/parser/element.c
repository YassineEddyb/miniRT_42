/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <ael-bach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 12:35:10 by ael-bach          #+#    #+#             */
/*   Updated: 2022/07/22 16:00:41 by ael-bach         ###   ########.fr       */
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


// int	identifier(char)
// {
	
// }


t_data	*check_and_fill(char **file, t_data *data)
{
	int		i;
	char	**tmp;

	i = -1;
	if (!file)
		error("ERROR : EMPTY FILE");
	while (file[++i])
	{
		tmp = ft_split_spaces(file[i], ' ');
		if (!ft_strncmp(tmp[0], "A", ft_strlen(tmp[0])))
			data->A = ambient_light(tmp);
		if (!ft_strncmp(tmp[0], "C", ft_strlen(tmp[0])))
			data->C = camera(tmp);
		if (!ft_strncmp(tmp[0], "L", ft_strlen(tmp[0])))
			data->L = light(tmp);
	
		// else
		// 	error("ERROR IN FILE");
		free_two_arr(tmp);
	}
	return (data);
}
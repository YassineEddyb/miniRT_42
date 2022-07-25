/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <ael-bach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 13:36:24 by ael-bach          #+#    #+#             */
/*   Updated: 2022/07/25 15:04:16 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/parser.h"

int	ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	j;

	if (*needle == 0)
	{
		return (0);
	}
	i = 0;
	while (haystack[i])
	{
		j = 0;
		while (needle[j] == haystack[i + j] && haystack[i + j])
		{
			if (needle[j + 1] == '\0' && haystack[i + j + 1] == '\0')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	calcul_len(char **av)
{
	char	*map;
	int		i;
	int		fd;

	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (-1);
	map = get_next_line(fd);
	if (!map)
		return (-1);
	i = 0;
	while (map)
	{
		free (map);
		map = get_next_line(fd);
		i++;
	}
	close (fd);
	return (i);
}

char	**ft_map(char **av)
{
	char	**map;
	int		i;
	int		j;
	int		fd;

	i = calcul_len(av);
	if (i < 0)
		return (NULL);
	j = i;
	map = malloc(sizeof(char *) * i + 1);
	if (!map)
		return (NULL);
	if (ft_strstr(av[1], ".tr") == 1)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
			return (NULL);
		i = 0;
		while (i < j)
			map[i++] = get_next_line(fd);
		close (fd);
		map[i] = NULL;
		return (map);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_data		*data;
	char		**file;
	// int			i;

	if (ac == 2)
	{
		file = ft_map(av);
		data = check_and_fill(file);
		printf("/*******************************/\n");
		printf("ambient ratio %f\n",data->A[0]->ratio);
		printf("ambient red   %d\n",data->A[0]->rgb.red);
		printf("ambient green %d\n",data->A[0]->rgb.green);
		printf("ambient blue  %d\n",data->A[0]->rgb.blue);
		printf("/*******************************/\n");
		printf("camera pos.x    %f\n",data->C[0]->pos.x);
		printf("camera pos.y    %f\n",data->C[0]->pos.y);
		printf("camera pos.z    %f\n",data->C[0]->pos.z);
		printf("camera normal.x %f\n",data->C[0]->normal.x);
		printf("camera normal.y %f\n",data->C[0]->normal.y);
		printf("camera normal.z %f\n",data->C[0]->normal.z);
		printf("camera FOV      %d\n",data->C[0]->fov);
		printf("/*******************************/\n");
		printf("L pos.x     %f\n",data->L[0]->pos.x);
		printf("L pos.y     %f\n",data->L[0]->pos.y);
		printf("L pos.z     %f\n",data->L[0]->pos.z);
		printf("L rgb.red   %d\n",data->L[0]->rgb.red);
		printf("L rgb.G     %d\n",data->L[0]->rgb.green);
		printf("L rgb.B     %d\n",data->L[0]->rgb.blue);
		printf("light ratio %f\n", data->L[0]->ratio);
		printf("/*******************************/\n");
		printf("sphere pos.x   %f\n",data->sp[0]->pos.x);
		printf("sphere pos.y   %f\n",data->sp[0]->pos.y);
		printf("sphere pos.z   %f\n",data->sp[0]->pos.z);
		printf("sphere rgb.red %d\n",data->sp[0]->rgb.red);
		printf("sphere rgb.G   %d\n",data->sp[0]->rgb.green);
		printf("sphere rgb.B   %d\n",data->sp[0]->rgb.blue);
		printf("diameter       %f\n", data->sp[0]->diameter);
		printf("/*******************************/\n");
		printf("plane pos.x    %f\n",data->pl[0]->pos.x);
		printf("plane pos.y    %f\n",data->pl[0]->pos.y);
		printf("plane pos.z    %f\n",data->pl[0]->pos.z);
		printf("plane normal.x %f\n",data->pl[0]->normal.x);
		printf("plane normal.y %f\n",data->pl[0]->normal.y);
		printf("plane normal.z %f\n",data->pl[0]->normal.z);
		printf("plane rgb.red  %d\n",data->pl[0]->rgb.red);
		printf("plane rgb.G    %d\n",data->pl[0]->rgb.green);
		printf("plane rgb.B    %d\n",data->pl[0]->rgb.blue);
		printf("/*******************************/\n");
		printf("clinder pos.x     %f\n",data->cy[0]->pos.x);
		printf("clinder pos.y     %f\n",data->cy[0]->pos.y);
		printf("clinder pos.z     %f\n",data->cy[0]->pos.z);
		printf("clinder normal.x  %f\n",data->cy[0]->normal.x);
		printf("clinder normal.y  %f\n",data->cy[0]->normal.y);
		printf("clinder normal.z  %f\n",data->cy[0]->normal.z);
		printf("clinder rgb.red   %d\n",data->cy[0]->rgb.red);
		printf("clinder rgb.G     %d\n",data->cy[0]->rgb.green);
		printf("clinder rgb.B     %d\n",data->cy[0]->rgb.blue);
		printf("cylinder diameter %f\n",data->cy[0]->diameter);
		printf("cylinder height   %f\n",data->cy[0]->height);
		printf("/*******************************/\n");
		// if (!map)
		// {
		// 	printf("FILE/SCENE: ERROR\n");
		// 	return (1);
		// }
	}
}
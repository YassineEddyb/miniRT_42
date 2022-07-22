/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <ael-bach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 13:36:24 by ael-bach          #+#    #+#             */
/*   Updated: 2022/07/22 16:00:27 by ael-bach         ###   ########.fr       */
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
		data = malloc (sizeof(t_data));
		data = check_and_fill(file, data);
		/*******************************/
		printf("ratio %f\n",data->A->ratio);
		printf("red %d\n",data->A->rgb.red);
		printf("green %d\n",data->A->rgb.green);
		printf("blue %d\n",data->A->rgb.blue);
		printf("/*******************************/\n");
		printf("pos.x %f\n",data->C->pos.x);
		printf("pos.y %f\n",data->C->pos.y);
		printf("pos.z %f\n",data->C->pos.z);
		printf("normal.x %f\n",data->C->normal.x);
		printf("normal.y %f\n",data->C->normal.y);
		printf("normal.z %f\n",data->C->normal.z);
		printf("FOV %d\n",data->C->fov);
		printf("/*******************************/\n");
		printf("L pos.x %f\n",data->L->pos.x);
		printf("L pos.y %f\n",data->L->pos.y);
		printf("L pos.z %f\n",data->L->pos.z);
		printf("L rgb.red %d\n",data->L->rgb.red);
		printf("L rgb.G %d\n",data->L->rgb.green);
		printf("L rgb.B %d\n",data->L->rgb.blue);
		printf("light ratio %f\n", data->L->ratio);
		printf("/*******************************/\n");
		
		// if (!map)
		// {
		// 	printf("FILE/SCENE: ERROR\n");
		// 	return (1);
		// }
		// i = 0;
		// while(map[i])
		// 	printf("%s\n",map[i++]);
	}
}
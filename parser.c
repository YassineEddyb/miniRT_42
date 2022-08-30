/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 13:36:24 by ael-bach          #+#    #+#             */
/*   Updated: 2022/08/29 21:39:36 by yed-dyb          ###   ########.fr       */
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
		error("ERROR : FILE");
	map = get_next_line(fd);
	if (!map)
		error("ERROR : file");
	i = 1;
	while (map)
	{
		free (map);
		map = get_next_line(fd);
		i++;
	}
	free (map);
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
	map = malloc(sizeof(char *) * (i + 1));
	if (!map)
		return (NULL);
	if (ft_strstr(av[1], ".rt") == 1)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
			error("ERROR : OPEN FILE");
		i = -1;
		while (++i < j)
			map[i] = get_next_line(fd);
		map[i] = NULL;
		close (fd);
		return (map);
	}
	return (NULL);
}

t_world	*parser(int ac, char **av)
{
	t_world		*data;
	char		**file;
	// int			i;

	if (ac == 2)
	{
		file = ft_map(av);
		data = check_and_fill(file);
	}
	return (data);
}
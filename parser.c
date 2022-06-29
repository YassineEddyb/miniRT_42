/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <ael-bach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 13:36:24 by ael-bach          #+#    #+#             */
/*   Updated: 2022/06/29 20:06:00 by ael-bach         ###   ########.fr       */
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
		map[i] = NULL;
		close (fd);
	}
	else
		return (NULL);
	return (map);
}

int	main(int ac, char **av)
{
	char		**map;
	int			i;

	if (ac == 2)
	{
		map = ft_map(av);
		if (!map)
		{
			printf("FILE/SCENE: ERROR\n");
			return (1);
		}
		i = 0;
		while(map[i])
			printf("%s\n",map[i++]);
	}
}
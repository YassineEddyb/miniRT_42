/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <ael-bach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 10:34:40 by ael-bach          #+#    #+#             */
/*   Updated: 2022/06/30 16:50:48 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_getsave(char *save)
{
	int		j;
	int		i;
	char	*dst;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	dst = malloc (sizeof(char *) * (ft_strlen(save) - i));
	if (!dst)
		return (NULL);
	j = 0;
	while (save[i] && save[++i])
	{
		dst[j++] = save[i];
	}
	dst[j] = '\0';
	free (save);
	return (dst);
}

char	*ft_getline(char *save)
{
	int		j;
	int		i;
	char	*dst;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (save[i] == '\n')
		dst = malloc (sizeof(char) * i + 2);
	else
		dst = malloc (sizeof(char) * i + 1);
	if (!dst)
		return (NULL);
	j = 0;
	while (save[j] && save[j] != '\n')
	{
		dst[j] = save[j];
		j++;
	}
	dst[j] = '\0';
	return (dst);
}

char	*ft_save(int fd, char *save)
{
	char	*buff;
	int		ret;

	buff = malloc(1 + 1);
	if (!buff)
		return (NULL);
	buff[0] = '\0';
	ret = 1;
	while (ft_strchr(buff, '\n') == 0 && ret != 0)
	{
		ret = read (fd, buff, 1);
		if (ret == -1)
		{
			free (buff);
			buff = NULL;
			return (NULL);
		}
		buff[ret] = '\0';
		save = ft_strjoin(save, buff);
	}
	free (buff);
	return (save);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save;

	if (fd < 0)
		return (NULL);
	save = ft_save(fd, save);
	if (!save)
		return (NULL);
	if (!save[0])
	{
		free (save);
		save = NULL;
		return (NULL);
	}
	line = ft_getline(save);
	save = ft_getsave(save);
	return (line);
}

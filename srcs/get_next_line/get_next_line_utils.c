/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 11:12:58 by ael-bach          #+#    #+#             */
/*   Updated: 2021/11/28 23:41:56 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*p;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	p = malloc (sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!p)
		return (NULL);
	i = 0;
	while (s1 && s1[i] != '\0')
	{
		p[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j] != '\0')
	{
		p[i] = s2[j];
		i++;
		j++;
	}
	p[i] = '\0';
	free (s1);
	return (p);
}

int	ft_strchr(const char *s, int c)
{
	int		i;
	char	*p;
	char	c1;

	p = (char *)s;
	c1 = (char)c;
	if (!s)
		return (0);
	i = 0;
	while (p[i] != '\0' && p[i] != c1)
	{
		i++;
	}
	if (p[i] == c1)
	{
		return (1);
	}
	return (0);
}

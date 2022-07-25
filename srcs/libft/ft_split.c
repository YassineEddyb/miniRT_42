/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 14:27:37 by ael-bach          #+#    #+#             */
/*   Updated: 2021/11/17 23:56:03 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numtab(char *s, char c)
{
	int		i;
	int		num_tab;

	i = 0;
	num_tab = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i])
			num_tab++;
		while (s[i] != c && s[i])
			i++;
	}
	return (num_tab);
}

static char	**ft_alloc(char const *s, char c)
{
	char	**tab;
	int		i;
	int		j;
	int		start;
	int		numtab;

	numtab = ft_numtab((char *)s, c);
	tab = malloc (sizeof(char *) * (numtab + 1));
	if (!tab)
		return (NULL);
	i = 0;
	j = 0;
	while (j < numtab)
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		tab[j] = ft_substr(s, start, (i - start));
		j++;
	}
	tab[j] = NULL;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**p;

	if (!s)
		return (NULL);
	p = ft_alloc(s, c);
	return (p);
	free (p);
}

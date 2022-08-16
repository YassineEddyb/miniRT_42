/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <ael-bach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 13:06:10 by ael-bach          #+#    #+#             */
/*   Updated: 2022/07/22 13:12:40 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/parser.h"

static int	ft_numtab(char *s, char c)
{
	int		i;
	int		num_tab;

	i = 0;
	num_tab = 0;
	while (s[i])
	{
		while (s[i] == c || s[i] == '\t')
			i++;
		if (s[i] != c && s[i] != '\t' && s[i])
			num_tab++;
		while (s[i] != c && s[i] != '\t' && s[i])
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
		while (s[i] == c || s[i] == '\t')
			i++;
		start = i;
		while (s[i] && s[i] != c && s[i] != '\t')
			i++;
		tab[j] = ft_substr(s, start, (i - start));
		j++;
	}
	tab[j] = NULL;
	return (tab);
}

char	**ft_split_spaces(char const *s, char c)
{
	char	**p;

	if (!s)
		return (NULL);
	p = ft_alloc(s, c);
	return (p);
	free (p);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 12:16:19 by ael-bach          #+#    #+#             */
/*   Updated: 2021/11/18 22:39:21 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	len_s;
	size_t	len_d;

	if (!dst && !dstsize)
		return (ft_strlen(src));
	i = 0;
	while (dst[i] != '\0')
		i++;
	len_d = i;
	len_s = ft_strlen(src);
	j = 0;
	while (i + 1 < dstsize && src[j] != '\0')
	{
		dst[i] = src[j];
		j++;
		i++;
	}
	dst[i] = '\0';
	if (i > dstsize)
		return (len_s + dstsize);
	return (len_s + len_d);
}

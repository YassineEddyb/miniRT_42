/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 21:19:05 by ael-bach          #+#    #+#             */
/*   Updated: 2021/11/17 19:21:33 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*mapi;
	unsigned int	i;
	unsigned int	len;

	if (!s)
		return (0);
	len = ft_strlen(s);
	mapi = malloc (sizeof(char) * len + 1);
	if (!mapi)
		return (NULL);
	i = 0;
	while (i < len)
	{
		mapi[i] = f(i, s[i]);
		i++;
	}
	mapi[i] = '\0';
	return (mapi);
}

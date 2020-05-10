/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 21:12:34 by sghezn            #+#    #+#             */
/*   Updated: 2019/04/08 14:37:36 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*res;

	res = (0);
	while (*s)
	{
		if (*s == c)
			res = ((char*)s);
		s++;
	}
	if (res)
		return (res);
	if (c == '\0')
		return ((char*)s);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 21:17:11 by sghezn            #+#    #+#             */
/*   Updated: 2020/05/10 01:22:21 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int	i;
	int	j;

	if (ft_strlen(needle) == 0)
		return ((char*)haystack);
	i = 0;
	while (haystack[i])
	{
		if (haystack[i] == needle[0])
		{
			j = 0;
			while (needle[j] != '\0' && haystack[i + j] == needle[j])
				j++;
			if (needle[j] == '\0')
				return ((char*)&haystack[i]);
		}
		i++;
	}
	return (0);
}

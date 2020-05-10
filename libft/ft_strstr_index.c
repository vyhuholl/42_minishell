/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr_index.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 01:16:26 by sghezn            #+#    #+#             */
/*   Updated: 2020/05/10 01:22:31 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strstr_index(const char *haystack, const char *needle)
{
	int	i;
	int	j;

	if (ft_strlen(needle) == 0)
		return (0);
	i = 0;
	while (haystack[i])
	{
		if (haystack[i] == needle[0])
		{
			j = 0;
			while (needle[j] != '\0' && haystack[i + j] == needle[j])
				j++;
			if (needle[j] == '\0')
				return (i);
		}
		i++;
	}
	return (-1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 20:37:56 by sghezn            #+#    #+#             */
/*   Updated: 2019/04/08 13:20:55 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*ptr_1;
	unsigned char	*ptr_2;
	size_t			i;

	ptr_1 = (unsigned char*)s1;
	ptr_2 = (unsigned char*)s2;
	i = 0;
	while (i < n)
	{
		if (ptr_1[i] != ptr_2[i])
			return (int)(ptr_1[i] - ptr_2[i]);
		i++;
	}
	return (0);
}

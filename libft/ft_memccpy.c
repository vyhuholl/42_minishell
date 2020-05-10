/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 20:09:18 by sghezn            #+#    #+#             */
/*   Updated: 2019/04/07 22:59:32 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*ptr_1;
	unsigned char	*ptr_2;
	size_t			i;

	ptr_1 = (unsigned char*)dst;
	ptr_2 = (unsigned char*)src;
	i = 0;
	while (i < n)
	{
		ptr_1[i] = ptr_2[i];
		if (ptr_1[i] == (unsigned char)c)
			return ((void*)(dst + i + 1));
		i++;
	}
	return (NULL);
}

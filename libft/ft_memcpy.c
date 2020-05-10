/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 20:04:26 by sghezn            #+#    #+#             */
/*   Updated: 2019/04/07 23:01:01 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
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
		i++;
	}
	return (dst);
}

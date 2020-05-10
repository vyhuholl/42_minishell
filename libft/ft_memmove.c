/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 20:15:49 by sghezn            #+#    #+#             */
/*   Updated: 2019/04/08 13:22:38 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*ptr_1;
	unsigned char	*ptr_2;
	size_t			i;

	ptr_1 = (unsigned char*)dst;
	ptr_2 = (unsigned char*)src;
	i = 0;
	if (ptr_2 < ptr_1)
		while (++i <= len)
			ptr_1[len - i] = ptr_2[len - i];
	else
		while (len-- > 0)
			*(ptr_1++) = *(ptr_2++);
	return (dst);
}

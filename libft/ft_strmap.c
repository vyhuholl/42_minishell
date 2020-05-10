/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 11:32:09 by sghezn            #+#    #+#             */
/*   Updated: 2019/04/08 14:33:44 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*ptr_1;
	char	*ptr_2;
	char	*result;

	if (!s || !(result = ft_memalloc((size_t)ft_strlen((char*)s) + 1)))
		return (NULL);
	ptr_1 = (char*)s;
	ptr_2 = result;
	while (*ptr_1)
		*(ptr_2++) = f(*(ptr_1++));
	return (result);
}

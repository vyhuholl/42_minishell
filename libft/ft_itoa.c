/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 14:37:49 by sghezn            #+#    #+#             */
/*   Updated: 2020/05/10 16:28:22 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbr_len(intmax_t n)
{
	intmax_t	n_copy;
	int			len;

	n_copy = (n < 0 ? -n : n);
	len = (n < 0 ? 2 : 1);
	while (n_copy /= 10)
		len++;
	return (len);
}

char		*ft_itoa(intmax_t n)
{
	intmax_t	n_copy;
	char		*res;
	int			sign;
	int			len;

	n_copy = (n < 0 ? -n : n);
	sign = (n < 0 ? 1 : 0);
	len = ft_nbr_len(n);
	if (!(res = ft_strnew(len + 1)))
		return (NULL);
	while (len - sign)
	{
		res[--len] = n_copy % 10 + 48;
		n_copy /= 10;
	}
	sign ? res[0] = '-' : 0;
	return (res);
}

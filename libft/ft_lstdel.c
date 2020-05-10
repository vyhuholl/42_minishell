/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 22:42:22 by sghezn            #+#    #+#             */
/*   Updated: 2019/04/08 14:17:59 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	t_list	*ptr;
	t_list	*temp;

	ptr = *alst;
	while (ptr)
	{
		temp = ptr;
		ft_lstdelone(&ptr, del);
		ptr = temp->next;
	}
	*alst = NULL;
}

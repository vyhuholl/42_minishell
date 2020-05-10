/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 22:16:16 by sghezn            #+#    #+#             */
/*   Updated: 2019/04/08 14:29:26 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_content_dup(void const *content, size_t content_size)
{
	char	*ptr_1;
	char	*ptr_2;
	void	*new;

	if (!(new = ft_memalloc(content_size)))
		return (NULL);
	ptr_1 = (char*)content;
	ptr_2 = (char*)new;
	while (*ptr_1)
		*(ptr_2++) = *(ptr_1++);
	return (new);
}

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*list;

	if (!(list = (t_list*)ft_memalloc(sizeof(t_list))))
		return (NULL);
	if (!content)
	{
		list->content = NULL;
		list->content_size = 0;
	}
	else
	{
		if (!(list->content = ft_content_dup(content, content_size)))
			return (NULL);
		list->content_size = content_size;
	}
	list->next = NULL;
	return (list);
}

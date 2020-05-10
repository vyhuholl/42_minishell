/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_spaces.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 13:44:26 by sghezn            #+#    #+#             */
/*   Updated: 2020/04/26 04:09:22 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_word_count(char const *s)
{
	int	res;
	int i;

	res = 0;
	i = 0;
	while (*(s + i))
	{
		while (ft_isspace(*(s + i)))
			i++;
		if (!ft_isspace(*(s + i)) && *(s + i) != '\0')
			res++;
		while (!ft_isspace(*(s + i)) && *(s + i) != '\0')
			i++;
	}
	return (res);
}

static void	ft_get_word_ptr(char const *s, char **start, char **end)
{
	if (!ft_isspace(*s) && *start == NULL)
		*start = (char*)s;
	if (ft_isspace(*s) && *start != NULL && *end == NULL)
		*end = (char*)s;
	if (!ft_isspace(*s) && *(s + 1) == '\0' && *start != NULL && *end == NULL)
		*end = (char*)(s + 1);
}

static char	*ft_get_word(char const *s, char **start, char **end)
{
	char	*word;

	word = ft_strsub(s, *start - s, *end - *start);
	*start = NULL;
	*end = NULL;
	return (word);
}

static char	**ft_free_split(char **s)
{
	char **ptr;

	ptr = s;
	while (*ptr)
		ft_strdel(ptr++);
	ft_strdel(s);
	return (NULL);
}

char		**ft_strsplit_spaces(char const *s)
{
	char	**res;
	char	*start;
	char	*end;
	int		i;
	int		j;

	start = NULL;
	end = NULL;
	i = -1;
	j = 0;
	if (!s || ft_word_count(s) == 0 ||
			!(res = (char**)malloc(sizeof(res) * (ft_word_count(s) + 1))))
		return (NULL);
	while (*(s + ++i))
	{
		ft_get_word_ptr(s + i, &start, &end);
		if (start && end)
			if (!(res[j++] = ft_get_word(s, &start, &end)))
				return (ft_free_split(res));
	}
	res[j] = NULL;
	return (res);
}

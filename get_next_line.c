/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 11:37:12 by sghezn            #+#    #+#             */
/*   Updated: 2020/03/12 18:19:48 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** Utility function to read the next line from the file descriptor.
*/

char	*ft_join(char *str, char *tab)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	i = 0;
	j = 0;
	if (str)
		i = ft_strlen(str);
	if (tab)
		j = ft_strlen(tab);
	ptr = (char*)malloc(sizeof(*ptr) * (i + j + 1));
	ft_memcpy(ptr, str, i);
	ft_memcpy(ptr + i, tab, j);
	ptr[i + j] = '\0';
	free(str);
	ft_bzero(tab, BUFF_SIZE + 1);
	return (ptr);
}

int		ft_end_line(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
	{
		str[i] = '\0';
		return (i);
	}
	else
		return (-1);
}

int		ft_check(char **str, char **tab, char **line)
{
	char	*ptr;
	int		res;

	*str = ft_join(*str, *tab);
	res = ft_end_line(*str);
	if (res > -1)
	{
		*line = ft_strdup(*str);
		ptr = *str;
		*str = ft_strdup(*str + res + 1);
		free(ptr);
		free(*tab);
		return (1);
	}
	free(*tab);
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	static char	*str[255];
	char		*temp;
	int			ret;
	int			res;

	temp = ft_strnew(BUFF_SIZE);
	if (fd < 0 || !line || BUFF_SIZE <= 0 || read(fd, temp, 0) < 0)
		return (-1);
	while ((ret = read(fd, temp, BUFF_SIZE)))
	{
		res = ft_check(&str[fd], &temp, line);
		if (res == 1)
			return (1);
		temp = ft_strnew(BUFF_SIZE);
	}
	if ((res = ft_check(&str[fd], &temp, line)))
		return (1);
	else if (ft_strlen(str[fd]) > 0)
	{
		*line = ft_strdup(str[fd]);
		ft_strdel(&str[fd]);
		return (1);
	}
	return (res);
}

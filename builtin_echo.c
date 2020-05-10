/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 19:03:45 by sghezn            #+#    #+#             */
/*   Updated: 2020/05/10 17:02:15 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_trim_quotes(char *s)
{
	char	*new_str;
	size_t	start;
	size_t	end;
	size_t	i;

	if (!s)
		return (NULL);
	end = ft_strlen(s) == 0 ? 0 : ft_strlen(s) - 1;
	start = 0;
	i = 0;
	while (s[start] == '"' || s[start] == '\'' || s[start] == '\\')
		start++;
	while ((s[end] == '"' || s[end] == '\'' || s[end] == '\\') && end != 0)
		end--;
	if (start > end)
		return (ft_strdup("\0"));
	new_str = (char*)ft_memalloc(sizeof(char) * (end - start + 2));
	if (!new_str)
		return (NULL);
	while (end >= start)
		new_str[i++] = s[start++];
	new_str[i] = '\0';
	return (new_str);
}

char	**ft_trim_arr(char **arr)
{
	char	**new;
	int		len;
	int		i;

	if (!arr)
		return (NULL);
	len = ft_arr_len(arr);
	if (!(new = (char**)ft_memalloc(sizeof(char*) * (len + 1))))
		ft_error("minishell: echo: memory allocation error");
	*(new + len) = 0;
	i = -1;
	while (++i < len)
		*(new + i) = ft_trim_quotes(*(arr + i));
	ft_free_lines(&arr);
	return (new);
}

void	ft_replace(char **str, char *old, char *new)
{
	char	*new_str;
	char	*old_str;
	int		start;
	int		len;

	if ((start = ft_strstr_index(*str, old)) != -1)
	{
		len = ft_strlen(*str) - ft_strlen(old);
		len += (new) ? ft_strlen(new) : 0;
		if (!(new_str = (char*)ft_memalloc(sizeof(char) * (len + 1))))
			ft_error("minishell: echo: memory allocation error");
		(start != 0) ? ft_strncpy(new_str, *str, start) : 0;
		if (new)
			(start != 0) ? ft_strcat(new_str, new) : ft_strcpy(new_str, new);
		if (ft_strlen(*str) > start + ft_strlen(old))
			ft_strcat(new_str, *str + start + ft_strlen(old));
		old_str = *str;
		*str = new_str;
		free(old_str);
	}
}

void	ft_echo(char **cmd)
{
	int		i;

	i = 0;
	while (cmd[++i])
	{
		ft_putstr(cmd[i]);
		if (cmd[i + 1])
			ft_putchar(' ');
	}
	ft_putchar('\n');
}

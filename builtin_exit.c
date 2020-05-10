/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 08:47:05 by sghezn            #+#    #+#             */
/*   Updated: 2020/05/10 17:15:38 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_is_number(char *s)
{
	int i;

	i = -1;
	while (s[++i])
		if (!(ft_isdigit(s[i]) || (i == 0 && (s[i] == '-' || s[i] == '+'))))
			return (-1);
	return (1);
}

void	ft_free_lines(char ***lines)
{
	char	**line;
	int		i;

	line = *lines;
	i = 0;
	while (*line)
	{
		ft_strdel(line);
		line = &(*lines)[++i];
	}
	ft_memdel((void**)lines);
}

void	ft_error(char *str)
{
	ft_putendl_fd(str, 2);
	exit(1);
}

void	ft_exit(char **cmd)
{
	if (ft_arr_len(cmd) > 2)
		ft_putendl_fd("minishell: exit: too many arguments", 2);
	else if (ft_arr_len(cmd) == 2 && ft_is_number(cmd[1]) == -1)
		ft_putendl_fd("minishell: exit: numeric exit status is required", 2);
	else if (ft_arr_len(cmd) == 1)
		exit(0);
	else
		exit(ft_atoi(cmd[1]));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 23:18:15 by sghezn            #+#    #+#             */
/*   Updated: 2020/04/26 00:40:11 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putchar('\n');
		ft_prompt();
		return ;
	}
}

void	ft_proc_signal_handler(int signo)
{
	if (wait(0) == -1)
		return ;
	if (signo == SIGINT)
		ft_putchar('\n');
}

int		ft_arr_len(char **arr)
{
	int	len;

	len = 0;
	while (*(arr + len))
		len++;
	return (len);
}

int		ft_get_var_index(char **env, char *key)
{
	char	*temp;
	int		eq;
	int		i;

	i = 0;
	while (*(env + i))
	{
		eq = ft_strchr_index(*(env + i), '=');
		temp = ft_strsub(*(env + i), 0, eq);
		if (ft_strequ(temp, key))
		{
			ft_strdel(&temp);
			return (i);
		}
		ft_strdel(&temp);
		i++;
	}
	return (-1);
}

char	*ft_get_var(char **env, char *key)
{
	char	*temp;
	int		eq;
	int		i;

	i = 0;
	while (*(env + i))
	{
		eq = ft_strchr_index(*(env + i), '=');
		temp = ft_strsub(*(env + i), 0, eq);
		if (ft_strequ(temp, key))
		{
			ft_strdel(&temp);
			return (ft_strdup(*(env + i) + eq + 1));
		}
		ft_strdel(&temp);
		i++;
	}
	return (NULL);
}

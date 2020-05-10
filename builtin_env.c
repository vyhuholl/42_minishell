/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 19:03:49 by sghezn            #+#    #+#             */
/*   Updated: 2020/05/10 17:00:54 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_str_count(char *str, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

char	*ft_find_env_var(char *str)
{
	int		i;
	int		j;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			if (str[i + 1] && str[i + 1] == '$')
				return (ft_strsub(str, i, 2));
			j = i + 1;
			while (str[j] && str[j] != '$' && str[j] != '/')
				j++;
			if (j > i)
				return (ft_strsub(str, i, j - i));
		}
	}
	return (NULL);
}

char	*ft_parse_prefix(char *str, char *prefix, int dir, char ***env)
{
	char	*var;

	if (dir > 1 || dir < -1 || (
			dir == -1 && ft_get_var_index(*env, "OLDPWD") == -1))
	{
		(str) ? ft_strdel(&str) : 0;
		(prefix) ? ft_strdel(&prefix) : 0;
		ft_putendl_fd("minishell: not enough directory stack entries", 2);
		return (NULL);
	}
	else if (dir == 0)
		var = ft_get_var(*env, "HOME");
	else if (dir == 1)
		var = ft_get_var(*env, "PWD");
	else
		var = ft_get_var(*env, "OLDPWD");
	ft_replace(&str, prefix, var);
	(prefix) ? ft_strdel(&prefix) : 0;
	(var) ? ft_strdel(&var) : 0;
	return (str);
}

void	ft_env(char **cmd, char ***env)
{
	char	**temp;

	if (ft_arr_len(cmd) > 1)
		ft_putendl_fd("minishell: env: too many arguments", 2);
	else
	{
		temp = *env;
		while (*temp)
			ft_putendl(*temp++);
	}
}

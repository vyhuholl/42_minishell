/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 01:36:35 by sghezn            #+#    #+#             */
/*   Updated: 2020/05/10 16:12:01 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_parse_path(char **arr)
{
	struct stat	dir_stat;

	if (**arr == '/' && (stat(*arr, &dir_stat)) == -1)
	{
		ft_putstr_fd("minishell: no such file or directory: ", 2);
		ft_putendl_fd(*arr, 2);
		ft_free_lines(&arr);
		return (0);
	}
	else if (S_ISDIR(dir_stat.st_mode))
	{
		if (ft_strlen(*arr) > 1 || access(*arr, X_OK) == -1)
		{
			ft_putstr_fd("minishell: permission denied: ", 2);
			ft_putendl_fd(*arr, 2);
			ft_free_lines(&arr);
			return (0);
		}
	}
	return (1);
}

char	*ft_tilde(char *str, char ***env)
{
	char	*prefix;
	int		dir;
	int		end;

	end = ft_strchr_index(str, '/');
	(end == -1) ? end = ft_strlen(str) : 0;
	prefix = ft_strsub(str, 0, end);
	if (prefix + 1 && (ft_is_number(prefix + 1) == -1))
	{
		ft_putstr_fd("minishell: no such user or named directory: ", 2);
		ft_putendl_fd(prefix + 1, 2);
		(prefix) ? ft_strdel(&prefix) : 0;
		(str) ? ft_strdel(&str) : 0;
		return (NULL);
	}
	if (ft_strequ(prefix, "~"))
		dir = 0;
	else if (ft_strequ(prefix, "~-"))
		dir = -1;
	else if (ft_strequ(prefix, "~+"))
		dir = 1;
	else
		dir = ft_atoi(prefix + 1);
	return (ft_parse_prefix(str, prefix, dir, env));
}

char	*ft_parse_var(char *str, char ***env)
{
	char	*key;
	char	*var;

	while ((key = ft_find_env_var(str)) != NULL)
	{
		if (ft_strequ(key, "$$"))
			var = ft_itoa(((intmax_t)getpid()));
		else
			var = ft_get_var(*env, key + 1);
		if (ft_strlen(str) == ft_strlen(key) && !var)
		{
			(str) ? ft_strdel(&str) : 0;
			(key) ? ft_strdel(&key) : 0;
			return (NULL);
		}
		ft_replace(&str, key, var);
		(key) ? ft_strdel(&key) : 0;
		(var) ? ft_strdel(&var) : 0;
	}
	return (str);
}

char	**ft_parse_expansions(char **arr, char ***env)
{
	char		**new;
	int			len;
	int			i;

	len = ft_arr_len(arr);
	if (!(new = (char**)ft_memalloc(sizeof(char*) * (len + 1))))
		ft_error("minishell: memory allocation error");
	*(new + len) = 0;
	i = -1;
	while (++i < len)
	{
		*(new + i) = ft_parse_var(ft_strdup(*(arr + i)), env);
		if (*(new + i) && **(new + i) && **(new + i) == '~' &&
				!(*(new + i) = ft_tilde(*(new + i), env)))
		{
			ft_free_lines(&arr);
			ft_free_lines(&new);
			return (NULL);
		}
	}
	ft_free_lines(&arr);
	if (!ft_parse_path(new))
		return (NULL);
	return (new);
}

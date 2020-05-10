/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 19:03:58 by sghezn            #+#    #+#             */
/*   Updated: 2020/05/10 17:13:51 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_check_var(char *var)
{
	int	sep;
	int	i;

	if (!var)
		ft_putendl_fd("minishell: setenv: empty variable", 2);
	else if (ft_str_count(var, '=') != 1)
		ft_putendl_fd("minishell: setenv: more than one = or no = at all", 2);
	else if ((sep = ft_strchr_index(var, '=')) == 0 || !(var[sep + 1]))
		ft_putendl_fd("minishell: setenv: empty name or value", 2);
	else if (ft_isdigit(var[0]))
		ft_putendl_fd("minishell: setenv: name begins with a digit", 2);
	else
	{
		i = -1;
		while (++i < sep)
			if (!ft_isupper(var[i]) && !ft_isdigit(var[i]) && var[i] != '_')
			{
				ft_putstr_fd("minishell: setenv: invalid char in name: ", 2);
				ft_putendl_fd(&(var[i]), 2);
				return (0);
			}
		return (1);
	}
	return (0);
}

void	ft_add_var(char ***env, char *var)
{
	char	**new_env;
	char	**old_env;
	int		len;
	int		i;

	len = 1;
	if (*env)
		len += ft_arr_len(*env);
	if (!(new_env = (char**)ft_memalloc(sizeof(char*) * (len + 1))))
		ft_error("minishell: setenv: memory allocation error");
	*(new_env + len) = 0;
	i = 0;
	while (*env && *(*env + i))
	{
		*(new_env + i) = *(*env + i);
		i++;
	}
	*(new_env + i) = ft_strdup(var);
	old_env = *env;
	*env = new_env;
	free(old_env);
}

void	ft_change_var(char ***env, char *var)
{
	char	*key;
	char	*tmp;
	char	*old;
	int		i;

	key = ft_strsub(var, 0, ft_strchr(var, '=') - var);
	i = 0;
	while (*(*env + i))
	{
		tmp = ft_strsub(*(*env + i), 0,
			ft_strchr(*(*env + i), '=') - *(*env + i));
		if (ft_strequ(key, tmp))
		{
			old = *(*env + i);
			*(*env + i) = ft_strdup(var);
			ft_strdel(&tmp);
			ft_strdel(&old);
			break ;
		}
		ft_strdel(&tmp);
		i++;
	}
	ft_strdel(&key);
}

char	*ft_new_var(char **cmd)
{
	char	*var;

	if (!cmd[2])
		var = ft_strdup(cmd[1]);
	else
	{
		var = ft_strnew(ft_strlen(cmd[1]) + ft_strlen(cmd[2]) + 1);
		var = ft_strcat(ft_strcat(ft_strcpy(var, cmd[1]), "="), cmd[2]);
	}
	return (var);
}

void	ft_setenv(char **cmd, char ***env)
{
	char	*var;
	char	*key;

	if (ft_arr_len(cmd) == 1)
		ft_putendl("minishell: usage setenv NAME=value or setenv NAME value");
	else if (ft_arr_len(cmd) > 3)
		ft_putendl_fd("minishell: setenv: too many arguments", 2);
	else
	{
		var = ft_new_var(cmd);
		if (ft_check_var(var))
		{
			key = ft_strsub(var, 0, ft_strchr_index(var, '='));
			if (ft_get_var_index(*env, key) != -1)
				ft_change_var(env, var);
			else
				ft_add_var(env, var);
			ft_strdel(&key);
		}
		ft_strdel(&var);
	}
}

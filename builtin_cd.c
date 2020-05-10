/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 19:03:32 by sghezn            #+#    #+#             */
/*   Updated: 2020/05/10 17:01:11 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_cd_replace(char **cmd)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (ft_strstr_index(cwd, cmd[1]) == -1)
	{
		ft_putstr_fd("minishell: cd: string not in pwd: ", 2);
		ft_putendl_fd(cmd[1], 2);
		ft_strdel(&cwd);
		return (NULL);
	}
	ft_replace(&cwd, cmd[1], cmd[2]);
	return (cwd);
}

int		ft_path_err(char *path)
{
	struct stat	dir_stat;

	if ((stat(path, &dir_stat)) == -1)
		ft_putstr_fd("minishell: cd: no such file or directory: ", 2);
	else if (!S_ISDIR(dir_stat.st_mode))
		ft_putstr_fd("minishell: cd: not a directory: ", 2);
	else if (access(path, X_OK) == -1)
		ft_putstr_fd("minishell: cd: permission denied: ", 2);
	else
		return (1);
	ft_putendl_fd(path, 2);
	return (-1);
}

void	ft_change_dir(char *path, char ***env)
{
	char	*old_pwd;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (ft_path_err(path) != -1 && chdir(path) != -1)
	{
		ft_set_pwd(env);
		if (cwd != NULL)
		{
			old_pwd = ft_strjoin("OLDPWD=", cwd);
			if (ft_get_var_index(*env, "OLDPWD") != -1)
				ft_change_var(env, old_pwd);
			else
				ft_add_var(env, old_pwd);
			ft_strdel(&old_pwd);
		}
	}
	ft_strdel(&cwd);
}

void	ft_find_path(char **cmd, char ***env)
{
	char	path[PATH_MAX + 1];
	char	*var;

	var = NULL;
	ft_bzero(path, PATH_MAX + 1);
	if (ft_arr_len(cmd) == 1)
		var = ft_get_var(*env, "HOME");
	else if (ft_arr_len(cmd) == 2 && ft_strequ(cmd[1], "-"))
	{
		if (ft_get_var_index(*env, "OLDPWD") != -1)
			var = ft_get_var(*env, "OLDPWD");
		else
			var = getcwd(NULL, 0);
		ft_putendl(var);
	}
	else if (ft_arr_len(cmd) == 3)
		var = ft_cd_replace(cmd);
	if (!(var || (ft_arr_len(cmd) == 2 && !ft_strequ(cmd[1], "-"))))
		return ;
	(var) ? ft_strcpy(path, var) : ft_strcpy(path, cmd[1]);
	ft_change_dir(path, env);
	(var) ? ft_strdel(&var) : 0;
}

void	ft_cd(char **cmd, char ***env)
{
	if (ft_arr_len(cmd) > 3)
		ft_putendl_fd("minishell: cd: too many arguments", 2);
	else
		ft_find_path(cmd, env);
}

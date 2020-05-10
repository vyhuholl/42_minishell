/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 03:33:29 by sghezn            #+#    #+#             */
/*   Updated: 2020/05/10 12:25:38 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_check_path(char **cmd, char **paths, char **err)
{
	struct stat f_stat;
	char		*file;
	int			i;

	i = -1;
	while (paths[++i])
	{
		file = ft_strnew(ft_strlen(cmd[0]) + ft_strlen(paths[i]) + 1);
		file = ft_strcat(ft_strcat(ft_strcpy(file, paths[i]), "/"), cmd[0]);
		if ((stat(file, &f_stat)) != -1)
		{
			if ((f_stat.st_mode & S_IXUSR) != S_IXUSR)
				*err = ft_strdup("permission denied: ");
			else
			{
				ft_free_lines(&paths);
				return (file);
			}
		}
		ft_strdel(&file);
	}
	ft_free_lines(&paths);
	return (NULL);
}

int		ft_check_cwd(char **cmd, char **err, char ***env)
{
	struct stat	f_stat;

	if ((stat(cmd[0], &f_stat)) != -1)
	{
		if ((f_stat.st_mode & S_IXUSR) != S_IXUSR)
			*err = ft_strdup("permission denied: ");
		else
		{
			if (S_ISDIR(f_stat.st_mode))
			{
				if (ft_arr_len(cmd) == 1)
				{
					ft_change_dir(cmd[0], env);
					return (2);
				}
				*err = ft_strdup("permission denied: ");
				return (0);
			}
			return (1);
		}
	}
	(!(*err)) ? *err = ft_strdup("command not found: ") : 0;
	return (0);
}

char	*ft_check_cmd(char **cmd, char ***env)
{
	char	**paths;
	char	*path;
	char	*file;
	char	*err;

	err = NULL;
	if (!ft_strequ(cmd[0], "..") && (path = ft_get_var(*env, "PATH")))
	{
		paths = ft_strsplit(path, ':');
		ft_strdel(&path);
		if ((file = ft_check_path(cmd, paths, &err)) != NULL)
			return (file);
	}
	if (ft_check_cwd(cmd, &err, env) == 1)
		return (ft_strdup(cmd[0]));
	if (!err)
		return (NULL);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(err, 2);
	ft_putendl_fd(cmd[0], 2);
	ft_strdel(&err);
	return (NULL);
}

void	ft_fork(char *filename, char **cmd, char **env)
{
	pid_t	pid;

	pid = fork();
	if (signal(SIGINT, ft_proc_signal_handler) == SIG_ERR)
		ft_error("minishell: unable to catch the signal");
	if (pid == -1)
		ft_error("minishell: fork failed");
	else if (pid == 0)
	{
		if ((execve(filename, cmd, env)) == -1)
			ft_error("minishell: execve: an error has occurred");
	}
	else
		wait(&pid);
}

void	ft_execute(char **cmd, char ***env)
{
	char	*file;

	file = NULL;
	cmd = ft_parse_expansions(cmd, env);
	if (cmd == NULL)
		return ;
	if (ft_strequ(cmd[0], "cd"))
		ft_cd(cmd, env);
	else if (ft_strequ(cmd[0], "echo"))
		ft_echo(cmd);
	else if (ft_strequ(cmd[0], "env"))
		ft_env(cmd, env);
	else if (ft_strequ(cmd[0], "exit"))
		ft_exit(cmd);
	else if (ft_strequ(cmd[0], "setenv"))
		ft_setenv(cmd, env);
	else if (ft_strequ(cmd[0], "unsetenv"))
		ft_unsetenv(cmd, env);
	else if ((file = ft_check_cmd(cmd, env)) != NULL)
		ft_fork(file, cmd, *env);
	(file) ? ft_strdel(&file) : 0;
	ft_free_lines(&cmd);
}

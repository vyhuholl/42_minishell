/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 03:33:29 by sghezn            #+#    #+#             */
/*   Updated: 2020/05/16 19:18:50 by sghezn           ###   ########.fr       */
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
		if ((stat(file, &f_stat)) != -1 && !S_ISDIR(f_stat.st_mode))
		{
			if (access(file, X_OK) == -1)
				*err = ft_strdup("permission denied: ");
			else
				return (file);
		}
		ft_strdel(&file);
	}
	return (NULL);
}

int		ft_check_cwd(char **cmd, char **err)
{
	struct stat	f_stat;

	if ((stat(cmd[0], &f_stat)) != -1)
	{
		if (S_ISDIR(f_stat.st_mode))
			*err = ft_strdup("is a directory: ");
		else if (access(cmd[0], X_OK) == -1)
			*err = ft_strdup("permission denied: ");
		else
			return (1);
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
		file = ft_check_path(cmd, paths, &err);
		ft_strdel(&path);
		ft_free_lines(&paths);
		if (file != NULL)
			return (file);
	}
	if (ft_check_cwd(cmd, &err) == 1)
		return (ft_strdup(cmd[0]));
	(err) ? ft_putstr_fd("minishell: ", 2) : 0;
	(err) ? ft_putstr_fd(err, 2) : 0;
	(err) ? ft_putendl_fd(cmd[0], 2) : 0;
	(err) ? ft_strdel(&err) : 0;
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
	if (!cmd || !*cmd || !**cmd)
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

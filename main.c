/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 18:43:59 by sghezn            #+#    #+#             */
/*   Updated: 2020/05/10 01:09:55 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_copy_env(char **envp)
{
	char	**env;
	int		len;
	int		i;

	len = ft_arr_len(envp);
	if (!(env = (char**)ft_memalloc(sizeof(char*) * (len + 1))))
		ft_error("minishell: memory allocation error");
	*(env + len) = 0;
	i = 0;
	while (i < len)
	{
		*(env + i) = ft_strdup(*(envp + i));
		i++;
	}
	return (env);
}

void	ft_set_pwd(char ***env)
{
	char	*new_pwd;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	new_pwd = ft_strjoin("PWD=", cwd);
	if (ft_get_var_index(*env, "PWD") != -1)
		ft_change_var(env, new_pwd);
	else
		ft_add_var(env, new_pwd);
	ft_strdel(&new_pwd);
	ft_strdel(&cwd);
}

void	ft_inc_shlvl(char ***env)
{
	char	*new_shlvl;
	char	*shlvl;
	char	*temp;

	if ((shlvl = ft_get_var(*env, "SHLVL")) != NULL)
	{
		new_shlvl = ft_itoa(ft_atoi(shlvl) + 1);
		temp = shlvl;
		shlvl = ft_strjoin("SHLVL=", new_shlvl);
		ft_strdel(&temp);
		ft_strdel(&new_shlvl);
		ft_change_var(env, shlvl);
		ft_strdel(&shlvl);
	}
	else
		ft_add_var(env, "SHLVL=1");
}

void	ft_prompt(void)
{
	ft_putstr(GREEN);
	ft_putstr("➜ ");
	ft_putstr(CYAN);
	ft_putstr("minishell");
	ft_putstr(YELLOW);
	ft_putstr(" ✗ ");
	ft_putstr(RESET);
}

int		main(int argc, char **argv, char **environ)
{
	char	**env;
	char	**cmd;
	char	*line;

	(void)argc;
	(void)argv;
	line = NULL;
	env = ft_copy_env(environ);
	ft_set_pwd(&env);
	ft_inc_shlvl(&env);
	while (42)
	{
		if (signal(SIGINT, ft_signal_handler) == SIG_ERR)
			ft_error("minishell: unable to catch the signal");
		ft_prompt();
		if (get_next_line(0, &line) == -1)
			ft_error("minishell: input reading error");
		if (!line)
			continue ;
		cmd = ft_trim_arr(ft_strsplit_spaces(line));
		ft_strdel(&line);
		(cmd && *cmd && **cmd) ? ft_execute(cmd, &env) : 0;
	}
	return (0);
}

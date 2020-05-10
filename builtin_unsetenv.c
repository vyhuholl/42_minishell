/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 19:04:02 by sghezn            #+#    #+#             */
/*   Updated: 2020/04/26 00:36:12 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_del_var(char ***env, int index)
{
	char	**new_env;
	char	**old_env;
	int		len;
	int		i;
	int		j;

	len = ft_arr_len(*env) - 1;
	if (!(new_env = (char**)ft_memalloc(sizeof(char*) * (len + 1))))
		ft_error("minishell: unsetenv: memory allocation error");
	*(new_env + len) = 0;
	i = 0;
	j = 0;
	while (*(*env + j))
	{
		if (j != index)
			*(new_env + i++) = *(*env + j++);
		else
			free(*(*env + j++));
	}
	old_env = *env;
	*env = new_env;
	free(old_env);
}

void	ft_unsetenv(char **cmd, char ***env)
{
	int	index;

	if (ft_arr_len(cmd) != 2)
		ft_putendl("minishell: usage unsetenv NAME");
	if ((index = ft_get_var_index(*env, cmd[1])) != -1)
		ft_del_var(env, index);
}

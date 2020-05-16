/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 18:43:41 by sghezn            #+#    #+#             */
/*   Updated: 2020/05/16 14:26:18 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "get_next_line.h"
# include <limits.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

# define GREEN "\033[1;32m"
# define CYAN "\033[1;36m"
# define YELLOW "\033[1;33m"
# define RESET "\033[0m"

char				*ft_cd_replace(char **cmd);
int					ft_path_err(char *path);
void				ft_change_dir(char *path, char ***env);
void				ft_find_path(char **cmd, char ***env);
void				ft_cd(char **cmd, char ***env);
char				*ft_trim_quotes(char *s);
char				**ft_trim_arr(char **arr);
void				ft_replace(char **str, char *old, char *new);
void				ft_echo(char **cmd);
int					ft_str_count(char *str, char c);
char				*ft_find_env_var(char *str);
char				*ft_parse_prefix(char *str, char *prefix,
									int dir, char ***env);
void				ft_env(char **cmd, char ***env);
int					ft_is_number(char *str);
void				ft_free_lines(char ***lines);
void				ft_error(char *str);
void				ft_exit(char **cmd);
int					ft_check_var(char *var);
void				ft_add_var(char ***env, char *var);
void				ft_change_var(char ***env, char *var);
char				*ft_new_var(char **cmd);
void				ft_setenv(char **cmd, char ***env);
void				ft_del_var(char ***env, int index);
void				ft_unsetenv(char **cmd, char ***env);
char				**ft_copy_env(char **envp);
void				ft_set_pwd(char ***env);
void				ft_inc_shlvl(char ***env);
void				ft_prompt(void);
char				*ft_tilde(char *str, char ***env);
char				*ft_parse_var(char *str, char ***env);
int					ft_parse_path(char **arr);
char				**ft_parse_expansions(char **arr, char ***env);
char				*ft_check_path(char **cmd, char **paths, char **err);
int					ft_check_cwd(char **cmd, char **err, char ***env);
char				*ft_check_cmd(char **cmd, char ***env);
void				ft_fork(char *filename, char **cmd, char **env);
void				ft_execute(char **cmd, char ***env);
void				ft_signal_handler(int signo);
void				ft_proc_signal_handler(int signo);
int					ft_arr_len(char **arr);
int					ft_get_var_index(char **env, char *key);
char				*ft_get_var(char **env, char *key);

#endif

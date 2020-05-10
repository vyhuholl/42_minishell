/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 11:37:08 by sghezn            #+#    #+#             */
/*   Updated: 2020/04/23 11:09:32 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>

# define BUFF_SIZE 32

char	*ft_join(char *str, char *tab);
int		ft_end_line(char *str);
int		ft_check(char **str, char **tab, char **line);
int		get_next_line(const int fd, char **line);

#endif

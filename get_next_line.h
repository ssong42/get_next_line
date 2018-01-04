/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/25 13:37:49 by ssong             #+#    #+#             */
/*   Updated: 2018/01/04 15:02:49 by ssong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "libft/libft.h"
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# define BUFF_SIZE 6000
int		get_next_line(const int fd, char **line);
typedef struct	s_double
{
	char			*line;
	char			*str;
	int				count;
	int				lines;
	int				fd;
	struct s_double	*next;
}					t_double;
#endif

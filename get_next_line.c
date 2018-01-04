/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 14:19:02 by ssong             #+#    #+#             */
/*   Updated: 2018/01/03 12:45:46 by ssong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_double	*addnode(t_double *tmp, int fd)
{
	tmp = malloc(sizeof(t_double));
	tmp->str = (char *)malloc(sizeof(char));
	tmp->str[0] = '\0';
	tmp->fd = fd;
	tmp->next = NULL;
	return (tmp);
}

t_double	*searchfd(t_double **array, int fd)
{
	t_double *tmp;

	tmp = *array;
	if (*array == NULL)
	{
		*array = addnode(tmp, fd);
		return (*array);
	}
	while (tmp->fd != fd)
	{
		if (tmp->next == NULL)
		{
			tmp = addnode(tmp, fd);
			tmp = tmp->next;
			return (tmp);
		}	
	}
	return (tmp);
}

int			set_string(t_double **array, char ***line)
{
	int i;
	
	i = 0;
	while ((*array)->str[i] != 0 && (*array)->str[i] != '\n')
			i++;
	if ((*array)->str[i] == 0)
	{
		**line = (*array)->str;
		if (i > 0)
			(*array)->str = ft_strdup((*array)->str + i);
		else if (i == 0)
			return (0);
	}
	else if ((*array)->str[i] == '\n')
	{
		(*array)->str[i] = 0;
		**line = ft_strdup((*array)->str);
		(*array)->str = ft_strdup((*array)->str + i + 1);
	}
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	int ret;
	static t_double *array = NULL;
	char buf[BUFF_SIZE + 1];
	t_double *tmp;

	if (fd < 0 || read(fd, buf, 0) < 0)
		return (-1);
	tmp = searchfd(&array, fd);
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		buf[ret] = 0;
		tmp->str = ft_strjoin(tmp->str, buf);
	}
	return (set_string(&tmp, &line));
}

/*
int main(int argc, char **argv)
{
	char	*line;
	int		fd;

	if (argc != 2)
		return (0);
	line = NULL;
	fd = open(argv[1], O_RDONLY);
	while (get_next_line(fd, &line))
	{
		ft_putstr(line);
		ft_putchar('\n');
		free(line);
	}
	return (0);
}
*/

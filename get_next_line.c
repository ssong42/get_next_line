/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 14:19:02 by ssong             #+#    #+#             */
/*   Updated: 2018/01/04 16:47:36 by ssong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_double	*addnode(t_double *tmp, int fd)
{ 
	t_double *end;

	end = malloc(sizeof(t_double));
	end->str = 0;
	end->fd = fd;
	end->next = NULL;
	if (tmp == NULL)
		return (end);
	else
		tmp->next = end;
	return (end);
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
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (tmp);
}

int			set_string(t_double **array, char ***line)
{
	int i;
	char *temp;

	i = 0;
	while ((*array)->str[i] != 0 && (*array)->str[i] != '\n')
			i++;
	if ((*array)->str[i] == 0)
	{
		**line = ft_strdup((*array)->str);
		if (i == 0)
			return (0);
		temp = ft_strdup((*array)->str + i);
		free ((*array)->str);
		(*array)->str = temp;
	}
	else if ((*array)->str[i] == '\n')
	{
		(*array)->str[i] = 0;
		**line = ft_strdup((*array)->str);
		temp = ft_strdup((*array)->str + i + 1);
		free ((*array)->str);
		(*array)->str = temp;
	}
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	int ret;
	static t_double *array = NULL;
	char buf[BUFF_SIZE + 1];
	t_double *tmp;
	char *temp;

	if (fd < 0 || read(fd, buf, 0) < 0)
		return (-1);
	tmp = searchfd(&array, fd);
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		buf[ret] = 0;
		temp = ft_strjoin(tmp->str, buf);
		free (tmp->str);
		tmp->str = temp;
	}
	return (set_string(&tmp, &line));
}

/*
int main(int argc, char **argv)
{
	char	*line;
	int		fd[4096];
	int		i;
	int		flag;

	flag = 0;
	i = 1;
	if (argc < 2)
		return (0);
	line = NULL;
	while (i < argc)
	{
		fd[i - 1] = open(argv[i], O_RDONLY);
		i++;
	}
	while (flag == 0)
	{
		flag = 1;
		i = 0;
		while (i < argc - 1)
		{
			if (get_next_line(fd[i], &line) == 1)
			{
				flag = 0;
				ft_putstr(line);
				ft_putchar('\n');
			}
			i++;
		}
	}
	ft_putstr(line);
	return (0);
}*/

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

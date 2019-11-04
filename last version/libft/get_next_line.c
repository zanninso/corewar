/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souarrak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 12:32:32 by souarrak          #+#    #+#             */
/*   Updated: 2019/04/12 20:50:03 by souarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_list_fd	*ft_check_or_creat(t_list_fd **list, int fd)
{
	t_list_fd	*ptr;

	ptr = *list;
	while (ptr)
	{
		if (ptr->fd == fd)
			return (ptr);
		ptr = ptr->next;
	}
	if ((ptr = (t_list_fd*)malloc(sizeof(*ptr))))
	{
		ptr->next = *list;
		ptr->d = NULL;
		ptr->s = 0;
		ptr->fd = fd;
	}
	*list = ptr;
	return (ptr);
}

static int			read_line(int fd, t_list_fd *p, char **line, int k)
{
	char	buf[BUFF_SIZE];
	int		ret;
	int		c;

	ret = 0;
	c = p->s;
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0 && ft_isln(buf, BUFF_SIZE) < 0)
	{
		if (!(*line = ft_realloc(*line, c + ret)))
			return (-1);
		ft_strncat(*line, buf, ret);
		c = c + ret;
		k = 1;
	}
	p->s = 0;
	if (ret == 0)
		return (k ? 1 : 0);
	if (ret == -1 || !(*line = ft_realloc(*line, ft_isln(buf, BUFF_SIZE) + c)))
		return (-1);
	ft_strncat(*line, buf, ft_isln(buf, BUFF_SIZE));
	p->s = ret - 1 - ft_isln(buf, BUFF_SIZE);
	if (!(p->d = ft_strndup((buf + ft_isln(buf, BUFF_SIZE) + 1), p->s)))
		return (-1);
	ft_bzero(buf, BUFF_SIZE);
	return (1);
}

static int			read_content(int fd, t_list_fd *p, char **line)
{
	int	k;

	k = 0;
	if (ft_isln(p->d, p->s) == -1)
	{
		if (!(*line = ft_strndup(p->d, p->s)))
			return (-1);
		free(p->d);
		k = 1;
		return (read_line(fd, p, line, k));
	}
	if (!(*line = ft_strndup(p->d, ft_isln(p->d, p->s))))
		return (-1);
	p->s = p->s - ft_isln(p->d, p->s) - 1;
	ft_memcpy(p->d, p->d + ft_isln(p->d, ft_strlen(p->d)) + 1, p->s);
	p->d = ft_realloc(p->d, p->s);
	return (!p->d ? -1 : 1);
}

int					get_next_line(const int fd, char **line)
{
	static t_list_fd	*lst;
	t_list_fd			*p;

	if (fd < 0 || !line)
		return (-1);
	*line = NULL;
	p = ft_check_or_creat(&lst, fd);
	if (p->s)
		return (read_content(fd, p, line));
	return (read_line(fd, p, line, 0));
}

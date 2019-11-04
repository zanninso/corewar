/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souarrak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 14:00:12 by souarrak          #+#    #+#             */
/*   Updated: 2019/05/07 14:22:06 by souarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "libft.h"
# define BUFF_SIZE 32

typedef struct				s_list_fd
{
	int						fd;
	int						s;
	char					*d;
	struct s_list_fd		*next;
}							t_list_fd;

int							get_next_line(const int fd, char **line);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souarrak <souarrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 01:11:12 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/08/07 16:30:03 by souarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static _Bool	is_room(char *line)
{
	char	*index1;
	char	*index2;

	index1 = ft_strreplace(line, ' ', '\0');
	index2 = ft_strreplace(index1, ' ', '\0');
	return (ft_isnbr(index1) && IS_INT(ft_atoi(index1)) && ft_isnbr(index2)
	&& IS_INT(ft_atoi(index2)) && !ft_isinstr(*line, "#L"));
}

static char		get_line_type(char *line)
{
	char	*tmp;

	if (!line)
		return (0);
	if (line[0] == '#' && line[1] == '#' && ft_strequ("start", line + 2))
		return ('s');
	if (line[0] == '#' && line[1] == '#' && ft_strequ("end", line + 2))
		return ('e');
	if (*line == '#')
		return ('c');
	if (ft_isnbr(line) && IS_INT(ft_atoi(line)) && ft_atoi(line) > 0)
		return ('a');
	if (is_room(line))
		return ('r');
	if ((tmp = ft_strreplace(line, '-', '\0')) && !ft_strchr(tmp, ' '))
		return ('l');
	return (0);
}

t_map_line		*get_nb_ants(t_map_line **map, char *line)
{
	char		type;
	t_map_line	*new;
	t_map_line	*tmp;

	tmp = *map;
	while (get_next_line(0, &line) > 0)
	{
		if (!(type = get_line_type(line)) || !ft_isinstr(type, "ca"))
			free_and_exit(NB_ANTS_ERR, NB_ANTS_STAT);
		if (!(new = ft_memalloc(sizeof(t_map_line))))
			free_and_exit(MALLOC_ERR, MALLOC_ERR_STAT);
		new->line = line;
		new->type = type;
		*map ? (tmp->next = new) : 0;
		!*map ? (*map = new) : 0;
		tmp = new;
		if (type == 'a' && ((g_lem_in.nb_ants = ft_atoi(line)) || 1))
			break ;
		line = NULL;
	}
	!line ? free_and_exit(NB_ANTS_ERR, NB_ANTS_STAT) : 0;
	return (tmp);
}

void			read_links(t_map_line *map, char *line, _Bool start, _Bool end)
{
	char		type;
	t_map_line	*new;
	int			gnl;

	gnl = 2;
	if (!start || !end)
		free_and_exit(ROOMS_NTFND_ERR, ROOMS_NTFND_STAT);
	ft_strreplace(line, 0, '-');
	while (line && gnl > 0)
	{
		if (!(type = get_line_type(line)) || !ft_isinstr(type, "cl"))
			free_and_exit(LINK_ERR, LINK_STAT);
		if (!(new = ft_memalloc(sizeof(t_map_line))))
			free_and_exit(MALLOC_ERR, MALLOC_ERR_STAT);
		new->line = line;
		new->type = type;
		map->next = new;
		map = map->next;
		line = NULL;
		gnl = get_next_line(0, &line);
	}
	ft_strdel(&line);
	gnl == 2 ? free_and_exit(LINKS_NTFND_ERR, LINKS_NTFND_STAT) : 0;
	gnl == -1 ? free_and_exit(MALLOC_ERR, MALLOC_ERR_STAT) : 0;
}

void			read_map(t_map_line **map)
{
	t_read_map	v;

	v = (t_read_map){NULL, get_nb_ants(map, NULL), NULL, 0, 0, 0, 0};
	while (get_next_line(0, &v.line) > 0)
	{
		if (!(v.type = get_line_type(v.line)) || !ft_isinstr(v.type, "seclr"))
			free_and_exit(ROOMS_ERR, ROOMS_STAT);
		if ((v.type == 'e' && v.end_readed) | (v.type == 's' && v.start_readed))
			free_and_exit(DOUBLE_ROOM_ERR, DOUBLE_ROOM_STAT);
		if ((v.prev_type == 'e' || v.prev_type == 's') && v.type != 'r')
			free_and_exit(ROOMS_NTFND_ERR, ROOMS_NTFND_STAT);
		if (v.type == 'l')
			return (read_links(v.tmp, v.line, v.start_readed, v.end_readed));
		if (!(v.new = ft_memalloc(sizeof(t_map_line))))
			free_and_exit(MALLOC_ERR, MALLOC_ERR_STAT);
		v.start_readed = v.type == 's' || v.start_readed;
		v.end_readed = v.type == 'e' || v.end_readed;
		v.new->line = v.line;
		v.new->type = v.type;
		v.tmp->next = v.new;
		v.tmp = v.tmp->next;
		g_lem_in.nb_rooms += v.type == 'r';
		v.prev_type = v.type;
	}
	free_and_exit(LINKS_NTFND_ERR, LINKS_NTFND_STAT);
}

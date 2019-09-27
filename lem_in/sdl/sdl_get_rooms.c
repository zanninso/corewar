/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_get_rooms.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souarrak <souarrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 16:56:48 by souarrak          #+#    #+#             */
/*   Updated: 2019/08/07 12:01:53 by souarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl.h"

static _Bool	is_comment(char *line, char *type_room, t_sdl_flag *flag)
{
	if (line[0] == '#' && line[1] == '#')
	{
		if (ft_strequ("start", line + 2) || ft_strequ("end", line + 2))
			*type_room = line[2];
		else if (ft_strequ("coord_z = TRUE", line + 2))
			flag->coord_z = TRUE;
		else if (ft_strequ("adjust = FALSE", line + 2))
			flag->adjust_rooms = FALSE;
		return (1);
	}
	if (line[0] == '#')
		return (1);
	return (0);
}

static void		get_room(t_sdl *sdl, t_room **rooms, char *line)
{
	char	*index;

	if (!((*rooms) = (t_room *)ft_memalloc(sizeof(t_room))))
		sdl_free_all_allocated_memory(sdl);
	index = ft_strchr(line, ' ');
	*index = '\0';
	if (!((*rooms)->name = ft_strdup(line)))
		sdl_free_all_allocated_memory(sdl);
	(*rooms)->coord.x = ft_atoi(index + 1);
	index = ft_strreplace(index + 1, ' ', '\0');
	(*rooms)->coord.y = ft_atoi(index);
	(*rooms)->previous = NULL;
	if (sdl->flag.coord_z)
	{
		index = ft_strreplace(index, ' ', '\0');
		(*rooms)->coord.z = ft_atoi(index);
	}
	else
		(*rooms)->coord.z = 0;
}

void			sdl_get_rooms(t_sdl *sdl, char **line)
{
	char	type;
	t_room	*tmp_rooms;

	type = 'r';
	tmp_rooms = NULL;
	while (get_next_line(0, line) > 0)
	{
		if (is_comment(*line, &type, &sdl->flag))
		{
			ft_strdel(line);
			continue;
		}
		if (!ft_strchr(*line, ' '))
			return ;
		get_room(sdl, &sdl->rooms, *line);
		sdl->rooms->type = type;
		sdl->rooms->next = tmp_rooms;
		type == 's' ? sdl->start = sdl->rooms : 0;
		type == 'e' ? sdl->end = sdl->rooms : 0;
		type = 'r';
		tmp_rooms = sdl->rooms;
		ft_strdel(line);
		sdl->nb_rooms++;
	}
}

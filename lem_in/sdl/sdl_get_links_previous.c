/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_get_links_previous.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 16:49:41 by souarrak          #+#    #+#             */
/*   Updated: 2019/08/06 23:06:40 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl.h"

t_link	*add_link(t_sdl *sdl, t_link **links, t_room *room)
{
	t_link	*ptr_links;

	ptr_links = *links;
	if (!ptr_links)
	{
		if (!(*links = (t_link *)ft_memalloc(sizeof(t_link))))
			sdl_free_all_allocated_memory(sdl);
		(*links)->room = room;
		(*links)->next = NULL;
		return (*links);
	}
	while (ptr_links->next)
	{
		if (ptr_links->room == room)
			return (NULL);
		if (!ptr_links->next)
			break ;
		ptr_links = ptr_links->next;
	}
	if (!(ptr_links->next = (t_link *)ft_memalloc(sizeof(t_link))))
		sdl_free_all_allocated_memory(sdl);
	ptr_links->next->room = room;
	ptr_links->next->next = NULL;
	return (ptr_links->next);
}

_Bool	add_links(t_sdl *sdl, char *line, char *index, t_tab_rooms *rooms)
{
	t_room	*room_1;
	t_room	*room_2;
	t_link	*link_room_1;
	t_link	*link_room_2;
	int		index_room;

	index_room = sdl_get_room(line, rooms, sdl->nb_rooms);
	room_1 = rooms[index_room].adress;
	index_room = sdl_get_room(index, rooms, sdl->nb_rooms);
	room_2 = rooms[index_room].adress;
	link_room_1 = add_link(sdl, &(room_1->links), room_2);
	link_room_2 = add_link(sdl, &(room_2->links), room_1);
	return (1);
}

void	add_previous(char *line, char *index, t_sdl *sdl, t_tab_rooms *rooms)
{
	t_room	*room_1;
	t_room	*room_2;
	int		index_room;

	index_room = sdl_get_room(line, rooms, sdl->nb_rooms);
	room_1 = rooms[index_room].adress;
	index_room = sdl_get_room(index, rooms, sdl->nb_rooms);
	room_2 = rooms[index_room].adress;
	if (room_1->type != 'e')
		room_1->previous = room_2;
	room_2->path = room_1;
	room_2 == sdl->start ? sdl->nb_paths++ : 0;
}

void	sdl_get_links(t_sdl *sdl, char **line)
{
	char	*index_room_2;
	t_link	*ptr;

	ptr = NULL;
	while (*line || get_next_line(0, line) > 0)
	{
		if (*line[0] == '#')
		{
			ft_strdel(line);
			continue;
		}
		if (!**line)
			break ;
		index_room_2 = ft_strreplace(*line, '-', '\0');
		add_links(sdl, *line, index_room_2, sdl->tab_rooms);
		ft_strdel(line);
	}
	ft_strdel(line);
}

void	sdl_get_paths(char **line, t_sdl *sdl, t_tab_rooms *table_rooms)
{
	char	*index_room_2;

	while (*line || get_next_line(0, line) > 0)
	{
		if (!**line)
			return ;
		if (*line[0] == '#')
		{
			ft_strdel(line);
			continue;
		}
		index_room_2 = ft_strreplace(*line, '-', '\0');
		add_previous(*line, index_room_2, sdl, table_rooms);
		ft_strdel(line);
	}
}

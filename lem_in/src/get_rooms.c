/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rooms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souarrak <souarrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 16:56:48 by souarrak          #+#    #+#             */
/*   Updated: 2019/09/27 18:40:36 by souarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_map_line		*get_rooms(t_rooms *rooms, t_map_line *map)
{
	size_t		i;
	char		type;

	i = 0;
	type = 0;
	while (i < g_lem_in.nb_rooms)
	{
		if (ft_isinstr(map->type, "seca"))
		{
			type = ft_isinstr(map->type, "se") ? map->type : type;
			map = map->next;
			continue;
		}
		if (i && get_room(rooms, map->line, i))
			free_and_exit(DOUBLE_ROOM_ERR, DOUBLE_ROOM_STAT);
		rooms[i].name = map->line;
		rooms[i].type = type;
		type == 's' ? g_lem_in.start_name = rooms[i].name : 0;
		type == 'e' ? g_lem_in.end_name = rooms[i].name : 0;
		sort_last_elem(rooms, i);
		type = 'r';
		map = map->next;
		i++;
	}
	return (map);
}

/*
** check if link exist
*/

static _Bool	is_linked(t_rooms *room1, t_rooms *room2)
{
	t_link	*links;

	links = room1->links;
	while (links)
	{
		if (links->room == room2)
			return (1);
		links = links->next;
	}
	return (0);
}

static void		add_links_to_rooms(char *name1, char *name2, t_rooms *rooms)
{
	t_rooms	*room1;
	t_rooms	*room2;
	t_link	*link_1;
	t_link	*link_2;
	size_t	nb_rooms;

	room1 = NULL;
	room2 = NULL;
	nb_rooms = g_lem_in.nb_rooms;
	if (!(room1 = get_room(rooms, name1, nb_rooms)) ||
		!(room2 = get_room(rooms, name2, nb_rooms)) || is_linked(room1, room2))
		free_and_exit(GET_LINK_ERR, GET_LINK_STAT);
	link_1 = (t_link *)ft_memalloc(sizeof(t_link));
	link_2 = (t_link *)ft_memalloc(sizeof(t_link));
	if (!link_1 || !link_2)
		free_and_exit(MALLOC_ERR, MALLOC_ERR_STAT);
	link_1->room = room2;
	link_2->room = room1;
	link_1->return_flow = &(link_2->direct_flow);
	link_2->return_flow = &(link_1->direct_flow);
	link_1->next = room1->links;
	room1->links = link_1;
	link_2->next = room2->links;
	room2->links = link_2;
}

void			get_links(t_map_line *map, t_rooms *rooms)
{
	while (map)
	{
		if (map->type != 'l')
		{
			map = map->next;
			continue;
		}
		add_links_to_rooms(map->line, ft_strreplace(map->line, 0, 0), rooms);
		map = map->next;
	}
}

void			check_if_start_end_linked(char *flag)
{
	int		i;
	t_link	*links;

	i = 1;
	links = g_lem_in.start->links;
	while (links)
	{
		if (links->room == g_lem_in.end)
		{
			!ft_strequ(flag, "-v") ? print_map(g_lem_in.map) : 0;
			while (i <= g_lem_in.nb_ants && !ft_strequ(flag, "-v"))
			{
				ft_putstr("L");
				ft_putnbr(i);
				ft_putstr("-");
				ft_putstr(g_lem_in.end->name);
				i == g_lem_in.nb_ants ? ft_putstr("\n") : ft_putstr(" ");
				i++;
			}
			free_and_exit(NULL, 0);
		}
		links = links->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_adjust_rooms.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souarrak <souarrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 17:52:12 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/08/07 12:05:14 by souarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl.h"

static void	adjust_coord_path(t_sdl sdl, t_link *links)
{
	t_room	*room;
	t_point	coord;
	int		i;

	coord.x = 1000 - (sdl.nb_paths / 2) * 200 - (sdl.nb_paths % 2 ? 200 : 100);
	while (links)
	{
		if (links->room->is_used)
		{
			i = 1;
			coord.x = coord.x + 200;
			coord.y = 200;
			room = links->room;
			while (room)
			{
				room->coord.x = coord.x;
				room->coord.y = i * coord.y;
				room->coord.z = generate_random(501);
				room = room->path;
				i++;
			}
		}
		links = links->next;
	}
}

static void	adjust_coord(t_link *links, int index)
{
	int	position_x;
	int	position_y;
	int	i;

	i = 1;
	position_x = 1000;
	position_y = 200 * index;
	links ? (links->room->coord.x = 1000) : 0;
	links ? (links->room->coord.y = position_y) : 0;
	links ? (links->room->coord.z = generate_random(1001)) : 0;
	links = links ? links->tmp_next : NULL;
	while (links)
	{
		links->room->coord.x = position_x + (200 * i);
		links->room->coord.y = position_y;
		links->room->coord.z = generate_random(1001);
		links = links->tmp_next;
		links ? (links->room->coord.x = position_x - (200 * i)) : 0;
		links ? (links->room->coord.y = position_y) : 0;
		links ? (links->room->coord.z = generate_random(1001)) : 0;
		links = links ? links->tmp_next : NULL;
		i++;
	}
}

static void	bfs(t_link *links, int index)
{
	t_link	*head;
	t_link	*tmp;
	t_link	*next_link;

	head = NULL;
	while (links)
	{
		tmp = links->room->links;
		while (tmp)
		{
			if (!tmp->room->bfs && tmp->room->is_used)
			{
				tmp->room->bfs = index;
				head ? (next_link->tmp_next = tmp) : 0;
				!head ? (head = tmp) : 0;
				next_link = tmp;
			}
			tmp = tmp->next;
		}
		tmp = links;
		links = links->tmp_next;
		tmp->tmp_next = NULL;
	}
	adjust_coord(head, index);
	head ? bfs(head, index + 1) : 0;
}

static void	initialise_bfs(t_room *rooms, t_sdl *sdl)
{
	double	count;

	count = 0;
	while (rooms)
	{
		rooms->bfs = 0;
		if (sdl->flag.path)
		{
			rooms->is_used = rooms->previous ? 1 : 0;
			rooms->type == 's' || rooms->type == 'e' ? rooms->is_used = 1 : 0;
			count++;
		}
		else
		{
			rooms->is_used = 1;
			count++;
		}
		rooms = rooms->next;
	}
	sdl->end->path = NULL;
	sdl->max_zoom_in = (double)MIN_ZOOM_IN + count /
		(double)MAX_NB_ROOMS * (double)MAX_ZOOM_IN;
	sdl->zoom = (double)sdl->coord.max_altitude / (double)sdl->max_zoom_in;
	sdl->radius_rooms = (double)(sdl->zoom * MAX_RADIUS);
}

void		readjust_coord(t_sdl *sdl)
{
	t_link	*ptr_links;

	initialise_bfs(sdl->rooms, sdl);
	sdl->start->bfs = -1;
	sdl->end->bfs = -1;
	if (sdl->flag.adjust_rooms)
	{
		if (!sdl->flag.path)
			bfs(&((t_link){sdl->start, POINT_NULL, 0, 0, NULL, NULL}), 1);
		else
			adjust_coord_path(*sdl, sdl->start->links);
		sdl->start->coord.x = 1000;
		sdl->start->coord.y = 10;
		sdl->start->coord.z = 0;
		sdl->end->coord.x = 1000;
		sdl->end->coord.y = 0;
		sdl->end->coord.z = 0;
		ptr_links = sdl->end->links;
		while (ptr_links)
		{
			if (ptr_links->room->coord.y + 200 > sdl->end->coord.y)
				sdl->end->coord.y = ptr_links->room->coord.y + 200;
			ptr_links = ptr_links->next;
		}
	}
}

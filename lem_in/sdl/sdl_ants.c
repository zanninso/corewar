/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_ants.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 14:11:40 by souarrak          #+#    #+#             */
/*   Updated: 2019/08/06 23:09:30 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl.h"

static void		sdl_initialise_ants(t_sdl *sdl, t_room *rooms)
{
	t_link	*ptr_links;

	while (rooms)
	{
		if (rooms->type == 'e')
		{
			ptr_links = rooms->links;
			while (ptr_links)
			{
				ptr_links->ant ? sdl->nb_ants_left-- : 0;
				ptr_links->ant = 0;
				ptr_links = ptr_links->next;
			}
		}
		rooms->full = rooms->ant ? TRUE : FALSE;
		rooms->ant = 0;
		rooms = rooms->next;
	}
}

_Bool			get_ants(t_sdl *sdl, t_tab_rooms *tab_rooms)
{
	char	*line;
	int		i;
	char	*index1;
	char	*index2;

	line = NULL;
	get_next_line(0, &line);
	if (!line)
		return (0);
	index1 = line;
	index2 = line;
	while (index1)
	{
		index2 = ft_strreplace(index2, ' ', '\0');
		index1++;
		i = sdl_get_room(ft_strchr(index1, '-') + 1, tab_rooms, sdl->nb_rooms);
		tab_rooms[i].adress->ant = ft_atoi(index1);
		index1 = index2;
	}
	ft_strdel(&line);
	return (1);
}

static void		sdl_calcul_coord_ants_end(t_sdl *sdl)
{
	t_point	d;
	t_link	*links;

	links = sdl->end->links;
	while (links)
	{
		if (links->ant)
		{
			d.x = links->room->coord.x - sdl->end->coord.x;
			d.y = links->room->coord.y - sdl->end->coord.y;
			d.z = links->room->coord.z - sdl->end->coord.z;
			links->coord_ant.x = -d.x * sdl->pos_ant + links->room->coord.x;
			links->coord_ant.y = -d.y * sdl->pos_ant + links->room->coord.y;
			links->coord_ant.z = -d.z * sdl->pos_ant + links->room->coord.z;
		}
		links->next_ant = links->room->full ? TRUE : FALSE;
		links = links->next;
	}
}

static void		sdl_calcul_coord_ants(t_sdl *sdl)
{
	t_point	d;
	t_room	*rooms;

	rooms = sdl->rooms;
	while (rooms)
	{
		if (rooms->type != 'e' && rooms->ant)
		{
			d.x = rooms->previous->coord.x - rooms->coord.x;
			d.y = rooms->previous->coord.y - rooms->coord.y;
			d.z = rooms->previous->coord.z - rooms->coord.z;
			rooms->coord_ant.x = -d.x * sdl->pos_ant + rooms->previous->coord.x;
			rooms->coord_ant.y = -d.y * sdl->pos_ant + rooms->previous->coord.y;
			rooms->coord_ant.z = -d.z * sdl->pos_ant + rooms->previous->coord.z;
		}
		rooms = rooms->next;
	}
	sdl_calcul_coord_ants_end(sdl);
}

void			sdl_draw_ants(t_sdl *sdl)
{
	sdl_calcul_coord_ants(sdl);
	sdl->pos_ant += sdl->speed_ants;
	if (sdl->pos_ant > 1)
	{
		sdl_initialise_ants(sdl, sdl->rooms);
		sdl->pos_ant = 0;
	}
}

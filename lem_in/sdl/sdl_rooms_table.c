/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_rooms_table.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 15:11:35 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/08/06 19:24:24 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl.h"

static void	ft_swap_rooms(t_tab_rooms *room_1, t_tab_rooms *room_2)
{
	t_tab_rooms	tmp;
	int			index;

	index = (*room_1).index;
	(*room_1).index = (*room_2).index;
	(*room_2).index = index;
	tmp = *room_1;
	*room_1 = *room_2;
	(*room_1).index = index;
	*room_2 = tmp;
}

t_tab_rooms	*sdl_generate_table_rooms(t_sdl *sdl, const int size)
{
	int		i;
	int		j;
	t_room	*rooms;

	i = 0;
	rooms = sdl->rooms;
	if (!(sdl->tab_rooms = (t_tab_rooms *)malloc(sizeof(t_tab_rooms) * size)))
		sdl_free_all_allocated_memory(sdl);
	while (i < size)
	{
		sdl->tab_rooms[i].name = rooms->name;
		sdl->tab_rooms[i].adress = rooms;
		sdl->tab_rooms[i].index = i;
		j = i;
		while (j &&
		ft_strcmp(sdl->tab_rooms[j].name, sdl->tab_rooms[j - 1].name) < 0)
		{
			ft_swap_rooms(&sdl->tab_rooms[j], &sdl->tab_rooms[j - 1]);
			j--;
		}
		i++;
		rooms = rooms->next;
	}
	return (sdl->tab_rooms);
}

int			sdl_get_room(const char *name, t_tab_rooms *table_rooms, int size)
{
	int	middle;
	int	diff;

	middle = size / 2;
	diff = ft_strcmp(table_rooms[middle].name, name);
	if (!size)
		return (-1);
	else if (diff == 0)
		return (table_rooms[middle].index);
	else if (diff > 0)
		return (sdl_get_room(name, table_rooms, middle));
	else
		return (sdl_get_room(name, table_rooms + middle, size - middle));
}

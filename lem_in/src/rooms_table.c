/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms_table.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 15:11:35 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/08/06 20:27:53 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	ft_swap_rooms(t_rooms *room_1, t_rooms *room_2)
{
	t_rooms	tmp;

	tmp = *room_1;
	*room_1 = *room_2;
	*room_2 = tmp;
}

void		sort_last_elem(t_rooms *rooms, size_t i)
{
	size_t	j;

	j = 0;
	while (j++ < i)
	{
		while (i && ft_strcmp(rooms[i].name, rooms[i - 1].name) < 0)
		{
			ft_swap_rooms(&rooms[i], &rooms[i - 1]);
			i--;
		}
	}
}

t_rooms		*get_room(t_rooms *rooms, const char *name, int size)
{
	int	middle;
	int	diff;

	middle = size / 2;
	diff = ft_strcmp(rooms[middle].name, name);
	if (!size || (size == 1 && diff))
		return (NULL);
	else if (diff == 0)
		return (&rooms[middle]);
	else if (diff > 0)
		return (get_room(rooms, name, middle));
	else
		return (get_room(rooms + middle, name, size - middle));
}

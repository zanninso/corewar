/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souarrak <souarrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 16:56:48 by souarrak          #+#    #+#             */
/*   Updated: 2019/09/27 17:44:36 by souarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

_Bool	print_ants(t_path *path)
{
	t_path_room	*room;
	_Bool		is_empty;
	_Bool		start;

	is_empty = 1;
	start = 1;
	while (path)
	{
		room = path->rooms;
		while (room)
		{
			if (room->ant && !(is_empty = 0))
			{
				!start ? ft_putstr(" ") : 0;
				ft_putstr("L");
				ft_putnbr(room->ant);
				ft_putstr("-");
				ft_putstr(room->name);
				start = 0;
			}
			room = room->next;
		}
		path = path->next;
	}
	return (is_empty);
}

void	move_ants_in_path(t_path_room *room)
{
	int tmp_ant_1;
	int tmp_ant_2;

	tmp_ant_1 = room->ant;
	room = room->next;
	while (room)
	{
		tmp_ant_2 = room->ant;
		room->ant = tmp_ant_1;
		tmp_ant_1 = tmp_ant_2;
		room = room->next;
	}
}

void	move_print_ants(t_path *path, int nb_ants)
{
	t_path	*ptr_path;
	_Bool	is_empty;
	int		ant_id;

	ant_id = 1;
	is_empty = 0;
	while (!is_empty)
	{
		ptr_path = path;
		while (ptr_path)
		{
			move_ants_in_path(ptr_path->rooms);
			if (nb_ants - ant_id >= 0 && ptr_path->rate <= nb_ants - ant_id)
				ptr_path->rooms->ant = ant_id++;
			else
				ptr_path->rooms->ant = 0;
			ptr_path = ptr_path->next;
		}
		is_empty = print_ants(path);
		!is_empty ? ft_putstr("\n") : 0;
	}
}

void	print_paths(t_path *path, char *start_name)
{
	t_path_room	*rooms;
	_Bool		is_start;

	while (path)
	{
		rooms = path->rooms;
		is_start = 1;
		while (rooms->next)
		{
			ft_putstr(is_start ? rooms->name : rooms->next->name);
			ft_putstr("-");
			ft_putendl(is_start ? start_name : rooms->name);
			!is_start ? (rooms = rooms->next) : 0;
			is_start = 0;
		}
		path = path->next;
	}
	ft_putstr("\n");
}

void	print_map(t_map_line *map)
{
	char	*tmp;

	while (map)
	{
		if (map->type == 'r')
		{
			ft_putstr(map->line);
			ft_putstr(" ");
			ft_putstr(tmp = ft_strchr(map->line, 0) + 1);
			ft_putstr(" ");
			ft_putendl(ft_strchr(tmp, 0) + 1);
		}
		else if (map->type == 'l')
		{
			ft_putstr(map->line);
			ft_putstr("-");
			ft_putendl(ft_strchr(map->line, 0) + 1);
		}
		else
			ft_putendl(map->line);
		map = map->next;
	}
	ft_putstr("\n");
}

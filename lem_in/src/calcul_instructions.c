/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul_instructions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souarrak <souarrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 01:40:44 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/09/27 18:53:50 by souarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			calc_instr(t_path *paths)
{
	int		i;
	size_t	arrived_ants;
	size_t	nb_ants;

	nb_ants = g_lem_in.nb_ants;
	arrived_ants = 0;
	i = 1;
	paths->rate = 0;
	while (paths->next)
	{
		if (((paths->next->steps - paths->steps) * i) + arrived_ants > nb_ants)
			break ;
		arrived_ants += (paths->next->steps - paths->steps) * i;
		paths = paths->next;
		paths->rate = arrived_ants;
		i++;
	}
	nb_ants -= arrived_ants;
	return ((nb_ants / i) + paths->steps + !!(nb_ants % i));
}

t_path_room	*get_path(t_rooms *room, int *steps)
{
	t_path_room	*ret;
	t_path_room	*new;
	t_path_room	*tmp;

	*steps = 0;
	ret = NULL;
	while (room)
	{
		room->bfs = *steps + 1;
		room->steps = 1;
		*steps = *steps + 1;
		if (!(new = (t_path_room *)ft_memalloc(sizeof(t_path_room))))
			free_and_exit(MALLOC_ERR, MALLOC_ERR_STAT);
		new->name = room->name;
		ret ? (tmp->next = new) : 0;
		!ret ? (ret = new) : 0;
		tmp = new;
		room = room->path;
	}
	return (ret);
}

void		add_path(t_path **path, t_path *new)
{
	t_path	*tmp;

	tmp = *path;
	if (!tmp || tmp->steps > new->steps)
	{
		new->next = *path;
		*path = new;
	}
	else
	{
		while (tmp->next && tmp->next->steps < new->steps)
			tmp = tmp->next;
		new->next = tmp->next;
		tmp->next = new;
	}
}

t_path		*get_paths_groupe(t_link *links)
{
	t_path	*path;
	t_path	*new;

	path = NULL;
	while (links)
	{
		if (links->room->path)
		{
			if (!(new = (t_path *)ft_memalloc(sizeof(t_path))))
				free_and_exit(MALLOC_ERR, MALLOC_ERR_STAT);
			if (!(new->rooms = get_path(links->room, &new->steps)))
				free_and_exit(MALLOC_ERR, MALLOC_ERR_STAT);
			new->steps -= 1;
			new->rate = g_lem_in.nb_ants + 1;
			add_path(&path, new);
		}
		links = links->next;
	}
	return (path);
}

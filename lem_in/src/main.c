/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souarrak <souarrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 16:49:41 by souarrak          #+#    #+#             */
/*   Updated: 2019/09/27 18:20:40 by souarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	add_to_queue(t_queue **queue, t_link *links, int level)
{
	t_queue	*node;

	if (!(node = (t_queue *)ft_memalloc(sizeof(t_queue))))
		free_and_exit(MALLOC_ERR, MALLOC_ERR_STAT);
	node->room = links->room;
	node->level = level;
	node->correction = !links->direct_flow && links->room->path ? 1 : 0;
	node->next = NULL;
	if (!*queue)
		*queue = node;
	else
	{
		(*queue)->next = node;
		*queue = (*queue)->next;
	}
}

void	set_start_end_bfs(void)
{
	g_lem_in.start->bfs = -1;
	g_lem_in.end->bfs = -1;
	g_lem_in.start->update_bfs = -1;
	g_lem_in.end->update_bfs = -1;
	g_lem_in.start->path = NULL;
}

void	get_rooms_links(void)
{
	t_map_line	*tmp_map;
	t_lem_in	*v;

	v = &g_lem_in;
	read_map(&v->map);
	if (!(v->rooms = ft_memalloc(sizeof(t_rooms) * v->nb_rooms)))
		free_and_exit(MALLOC_ERR, MALLOC_ERR_STAT);
	tmp_map = get_rooms(v->rooms, v->map);
	v->start = get_room(v->rooms, v->start_name, v->nb_rooms);
	v->end = get_room(v->rooms, v->end_name, v->nb_rooms);
	get_links(tmp_map, v->rooms);
	set_start_end_bfs();
}

void	find_paths(void)
{
	t_lem_in	*v;

	v = &g_lem_in;
	initialise_update_bfs(v->rooms, v->nb_rooms);
	add_to_queue(&v->queue, &((t_link){v->start, 0, NULL, NULL, NULL}), 0);
	while (increase_flow(v->queue, v->queue, 1))
	{
		v->start->path = NULL;
		update_paths(v->end);
		if (v->paths_gr1)
			v->paths_gr2 = get_paths_groupe(v->start->links);
		else
			v->paths_gr1 = get_paths_groupe(v->start->links);
		if (v->paths_gr2 && calc_instr(v->paths_gr2) < calc_instr(v->paths_gr1))
		{
			free_path(&v->paths_gr1);
			v->paths_gr1 = v->paths_gr2;
			v->paths_gr2 = NULL;
		}
		else
			free_path(&v->paths_gr2);
		initialise_update_bfs(v->rooms, v->nb_rooms);
		free_queue(&v->queue);
		add_to_queue(&v->queue, &((t_link){v->start, 0, NULL, NULL, NULL}), 0);
	}
}

int		main(int ac, char **av)
{
	g_lem_in = (t_lem_in){NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, 0, 0};
	get_rooms_links();
	check_if_start_end_linked(ac == 2 ? av[1] : NULL);
	find_paths();
	free_queue(&g_lem_in.queue);
	!g_lem_in.paths_gr1 ? free_and_exit(NO_SOLUTION_ERR, 9) : 0;
	print_map(g_lem_in.map);
	if (ac == 2 && ft_strequ(av[1], "-v"))
		print_paths(g_lem_in.paths_gr1, g_lem_in.start_name);
	move_print_ants(g_lem_in.paths_gr1, g_lem_in.nb_ants);
	free_and_exit(NULL, 0);
}

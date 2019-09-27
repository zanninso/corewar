/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souarrak <souarrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 17:53:46 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/08/07 14:33:48 by souarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		free_links(t_rooms *rooms, size_t nb_rooms)
{
	t_link	*links;
	t_link	*next_links;

	if (!rooms)
		return ;
	while (nb_rooms--)
	{
		links = rooms->links;
		while (links)
		{
			next_links = links->next;
			free(links);
			links = links->next;
		}
		rooms->links = NULL;
		rooms++;
	}
}

static void	free_path_rooms(t_path_room *rooms)
{
	t_path_room	*next_room;

	while (rooms)
	{
		next_room = rooms->next;
		free(rooms);
		rooms = next_room;
	}
	rooms = NULL;
}

void		free_queue(t_queue **queues)
{
	t_queue	*next_queue;
	t_queue	*queue;

	queue = *queues;
	while (queue)
	{
		next_queue = queue->next;
		free(queue);
		queue = next_queue;
	}
	*queues = NULL;
}

void		free_path(t_path **paths)
{
	t_path	*next_path;
	t_path	*path;

	path = *paths;
	while (path)
	{
		next_path = path->next;
		free_path_rooms(path->rooms);
		free(path);
		path = next_path;
	}
	*paths = NULL;
}

void		free_and_exit(const char *msg, int status)
{
	t_map_line	*next_map;
	int			fd;

	free_path(&g_lem_in.paths_gr1);
	free_path(&g_lem_in.paths_gr2);
	free_links(g_lem_in.rooms, g_lem_in.nb_rooms);
	while (g_lem_in.map)
	{
		next_map = g_lem_in.map->next;
		free(g_lem_in.map->line);
		free(g_lem_in.map);
		g_lem_in.map = next_map;
	}
	free(g_lem_in.rooms);
	fd = status ? 2 : 1;
	msg ? ft_putendl_fd(msg, fd) : 0;
	exit(status);
}

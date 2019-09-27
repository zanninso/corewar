/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_flow.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souarrak <souarrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 23:20:53 by souarrak          #+#    #+#             */
/*   Updated: 2019/09/27 18:40:00 by souarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	initialise_update_bfs(t_rooms *rooms, size_t nb_rooms)
{
	t_link	*ptr_links;
	size_t	i;

	i = 0;
	while (i < nb_rooms)
	{
		rooms[i].update_bfs = rooms[i].type == 's' ? -1 : 0;
		rooms[i].previous = NULL;
		if (!rooms[i].steps)
		{
			rooms[i].path = NULL;
			rooms[i].bfs = 0;
		}
		ptr_links = rooms[i].links;
		while (ptr_links)
		{
			ptr_links->previous = NULL;
			ptr_links = ptr_links->next;
		}
		i++;
	}
}

_Bool	check_do_correction(t_queue *queue, t_queue **last_node)
{
	t_queue	*c_queue;
	t_link	*ptr_links;

	if (queue->correction && ((ptr_links = queue->room->links) || 1))
	{
		while (ptr_links->direct_flow != -1)
			ptr_links = ptr_links->next;
		if (ptr_links->room->type == 's' || ptr_links->room->update_bfs)
			return (0);
		ptr_links->room->previous = ptr_links;
		ptr_links->previous = queue->room->previous;
		queue->room->update_bfs = queue->room->bfs;
		c_queue = NULL;
		add_to_queue(&c_queue, ptr_links, 0);
		c_queue->room->update_bfs = c_queue->room->bfs;
		if (cor_flow(c_queue, c_queue, last_node, c_queue->room->bfs))
		{
			queue->room->update_bfs = 0;
			ft_memdel((void **)&c_queue);
			return (1);
		}
		queue->room->update_bfs = 0;
		ft_memdel((void **)&c_queue);
	}
	return (0);
}

_Bool	cor_flow(t_queue *c_queue, t_queue *last, t_queue **queue, int lv_queue)
{
	t_link *links;

	while (c_queue)
	{
		links = c_queue->room->links;
		if (check_do_correction(c_queue, &last))
			return (1);
		while (links && !c_queue->correction)
		{
			if (links->direct_flow < 1 && !links->room->update_bfs)
			{
				links->room->previous = links;
				links->previous = c_queue->room->previous;
				if (links->room->type == 'e')
					return (1);
				links->room->update_bfs = !links->direct_flow ?
					c_queue->room->update_bfs + 1 : links->room->bfs;
				links->room->update_bfs < lv_queue ? add_to_queue(&last,
						links, 0) : add_to_queue(queue, links, lv_queue);
			}
			links = links->next;
		}
		c_queue = c_queue->next;
	}
	return (0);
}

_Bool	increase_flow(t_queue *queue, t_queue *last_node, int level)
{
	t_link *links;

	while (queue)
	{
		links = queue->room->links;
		if (check_do_correction(queue, &last_node))
			return (1);
		while (links && !queue->correction)
		{
			if (links->direct_flow < 1 && !links->room->update_bfs)
			{
				links->room->previous = links;
				links->previous = queue->room->previous;
				links->room->update_bfs = level;
				if (links->room->type == 'e')
					return (1);
				add_to_queue(&last_node, links, level);
			}
			links = links->next;
		}
		queue->next && queue->next->level > queue->level ? level++ : 0;
		queue = queue->next;
	}
	return (0);
}

void	update_paths(t_rooms *rooms)
{
	t_link *links;

	links = rooms->previous;
	while (links)
	{
		if (links->direct_flow == 0)
		{
			links->direct_flow = 1;
			*(links->return_flow) = -1;
			links->previous ? links->previous->room->path = links->room : 0;
		}
		else if (links->direct_flow == -1)
		{
			links->direct_flow = 0;
			*(links->return_flow) = 0;
			if (links->previous && links->previous->direct_flow == -1)
				links->previous->room->path = NULL;
		}
		links = links->previous;
	}
}

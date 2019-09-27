/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souarrak <souarrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 19:24:41 by souarrak          #+#    #+#             */
/*   Updated: 2019/08/06 18:09:28 by souarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl.h"

void	sdl_print_previous(t_link *ptr_links, t_sdl sdl, SDL_Renderer *rnd)
{
	t_room	*room_1;
	t_room	*room_2;
	double	x;
	double	y;

	SDL_SetRenderDrawColor(rnd, COLOR_PATHS, SDL_ALPHA_OPAQUE);
	while (ptr_links)
	{
		room_1 = sdl.end;
		room_2 = ptr_links->room;
		while (room_2)
		{
			x = room_2->coord.x;
			y = room_2->coord.y;
			if (room_1->is_used && room_2->is_used)
				SDL_RenderDrawLine(rnd, room_1->coord.x, room_1->coord.y, x, y);
			room_1 = room_2;
			room_2 = room_2->previous;
		}
		ptr_links = ptr_links->next;
	}
}

void	sdl_print_links(t_room *rooms, t_sdl *sdl, SDL_Renderer *rnd)
{
	t_link *ptr_links;
	double x1;
	double y1;

	while (rooms)
	{
		ptr_links = rooms->links;
		while (ptr_links)
		{
			if (ptr_links->room->previous || rooms->previous)
				SDL_SetRenderDrawColor(rnd, COLOR_PATHS, SDL_ALPHA_OPAQUE);
			else
				SDL_SetRenderDrawColor(rnd, COLOR_LINKS, SDL_ALPHA_OPAQUE);
			x1 = ptr_links->room->coord.x;
			y1 = ptr_links->room->coord.y;
			if (sdl->flag.path && ptr_links->room->is_used && rooms->is_used)
				SDL_RenderDrawLine(rnd, rooms->coord.x, rooms->coord.y, x1, y1);
			else if (!sdl->flag.path)
				SDL_RenderDrawLine(rnd, rooms->coord.x, rooms->coord.y, x1, y1);
			ptr_links = ptr_links->next;
		}
		rooms = rooms->next;
	}
}

void	sdl_print_ants(t_sdl sdl, t_room *rooms, double radius)
{
	t_link *ptr_links;

	if (rooms->type != 'e' && rooms->ant)
		filledCircleRGBA(sdl.renderer, rooms->coord_ant.x,
		rooms->coord_ant.y, radius * 0.4, COLOR_ANT);
	else if (rooms->type == 'e' && rooms->ant && !sdl.flag.pause)
	{
		ptr_links = rooms->links;
		while (ptr_links)
		{
			if (ptr_links->ant)
				filledCircleRGBA(sdl.renderer, ptr_links->coord_ant.x,
				ptr_links->coord_ant.y, radius * 0.4, COLOR_ANT);
			ptr_links->ant = ptr_links->next_ant;
			ptr_links = ptr_links->next;
		}
	}
}

void	sdl_print_rooms_circle(t_sdl sdl, t_room *rooms, double radius)
{
	if (rooms->type == 's')
		filledCircleRGBA(sdl.renderer, rooms->coord.x,
		rooms->coord.y, radius, COLOR_START);
	else if (rooms->type == 'e')
		filledCircleRGBA(sdl.renderer, rooms->coord.x,
		rooms->coord.y, radius, COLOR_END);
	else if (rooms->previous)
		filledCircleRGBA(sdl.renderer, rooms->coord.x,
		rooms->coord.y, radius, COLOR_ROOMS_PATH);
	else if (!sdl.flag.path)
		filledCircleRGBA(sdl.renderer, rooms->coord.x,
		rooms->coord.y, radius, COLOR_ROOMS);
}

void	sdl_print_rooms(t_room *rooms, t_sdl sdl)
{
	double	radius;
	t_point	point;

	radius = sdl.radius_rooms > 1000 ? 1000 : sdl.radius_rooms;
	while (rooms)
	{
		if (rooms->coord.x + radius > 0 && rooms->coord.x - radius < WIDTH * 2
		&& rooms->coord.y + radius > 0 && rooms->coord.y - radius < HEIGHT * 2)
		{
			sdl_print_ants(sdl, rooms, radius);
			sdl_print_rooms_circle(sdl, rooms, radius);
			point.x = rooms->coord.x;
			point.y = rooms->coord.y - radius * 1.4;
			if (sdl.flag.rooms_name && !sdl.flag.path && sdl.zoom > 0.03)
				sdl_putstr(sdl.renderer, rooms->name, point,
				sdl.font.rooms_name);
			if (sdl.flag.rooms_name && rooms->is_used && sdl.zoom > 0.03)
				sdl_putstr(sdl.renderer, rooms->name, point,
				sdl.font.rooms_name);
		}
		rooms = rooms->next;
	}
}

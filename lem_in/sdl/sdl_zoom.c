/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_zoom.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souarrak <souarrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 19:04:16 by souarrak          #+#    #+#             */
/*   Updated: 2019/08/07 12:08:59 by souarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl.h"

static _Bool	sdl_init_zoom_in(t_sdl *sdl)
{
	double	scale;

	if (sdl->coord.x.altitude < WIDTH - 100 &&
	sdl->coord.y.altitude < HEIGHT - 100)
	{
		if (SCREEN_HEIGHT / sdl->coord.y.altitude <
		SCREEN_WIDTH / sdl->coord.x.altitude)
			scale = (double)(SCREEN_HEIGHT - sdl->coord.y.max) /
			(double)(sdl->coord.y.max - MIDDLE_HEIGHT);
		else
			scale = (double)(SCREEN_WIDTH - sdl->coord.x.max) /
			(double)(sdl->coord.x.max - MIDDLE_WIDTH);
		scale ? sdl_zoom_in(sdl->rooms, sdl, scale) : 0;
		return (1);
	}
	return (0);
}

static _Bool	sdl_init_zoom_out(t_sdl *sdl)
{
	double	scale;

	if (sdl->coord.x.altitude > WIDTH || sdl->coord.y.altitude > HEIGHT)
	{
		if (sdl->coord.y.altitude / SCREEN_HEIGHT >
		sdl->coord.x.altitude / SCREEN_WIDTH)
			scale = (double)(sdl->coord.y.max - SCREEN_HEIGHT) /
			(double)(SCREEN_HEIGHT - MIDDLE_HEIGHT);
		else
			scale = (double)(sdl->coord.x.max - SCREEN_WIDTH) /
			(double)(SCREEN_WIDTH - MIDDLE_WIDTH);
		scale ? sdl_zoom_out(sdl->rooms, sdl, scale) : 0;
		return (1);
	}
	return (0);
}

void			sdl_init_zoom(t_sdl *sdl)
{
	sdl_init_scroll(sdl->rooms, sdl);
	sdl->mouse.x = MIDDLE_WIDTH;
	sdl->mouse.y = MIDDLE_HEIGHT;
	if (sdl_init_zoom_in(sdl))
		return ;
	sdl_init_zoom_out(sdl);
}

void			sdl_zoom_in(t_room *rooms, t_sdl *sdl, double scale)
{
	if (!sdl->zoom_in)
		return ;
	sdl_init_coord(&sdl->coord);
	while (rooms)
	{
		rooms->coord.x += (rooms->coord.x - sdl->mouse.x) * scale;
		rooms->coord.y += (rooms->coord.y - sdl->mouse.y) * scale;
		rooms->coord.z += (rooms->coord.z - sdl->mouse.z) * scale;
		if (rooms->type != 'e' && sdl->flag.pause)
		{
			rooms->coord_ant.x += (rooms->coord_ant.x - sdl->mouse.x) * scale;
			rooms->coord_ant.y += (rooms->coord_ant.y - sdl->mouse.y) * scale;
			rooms->coord_ant.z += (rooms->coord_ant.z - sdl->mouse.z) * scale;
		}
		if ((rooms->is_used && sdl->flag.path) || !sdl->flag.path)
			sdl_check_get_max_min_coord(rooms, &sdl->coord);
		rooms = rooms->next;
	}
	sdl_calcul_propreties(sdl);
}

void			sdl_zoom_out(t_room *rooms, t_sdl *sdl, double scale)
{
	double val;

	if (!sdl->zoom_out)
		return ;
	sdl_init_coord(&sdl->coord);
	while (rooms)
	{
		rooms->coord.x = (rooms->coord.x + scale * sdl->mouse.x) / (1 + scale);
		rooms->coord.y = (rooms->coord.y + scale * sdl->mouse.y) / (1 + scale);
		rooms->coord.z = (rooms->coord.z + scale * sdl->mouse.z) / (1 + scale);
		if (rooms->type != 'e' && sdl->flag.pause)
		{
			val = (rooms->coord_ant.x + scale * sdl->mouse.x) / (1 + scale);
			rooms->coord_ant.x = val;
			val = (rooms->coord_ant.y + scale * sdl->mouse.y) / (1 + scale);
			rooms->coord_ant.y = val;
			val = (rooms->coord_ant.z + scale * sdl->mouse.z) / (1 + scale);
			rooms->coord_ant.z = val;
		}
		if ((rooms->is_used && sdl->flag.path) || !sdl->flag.path)
			sdl_check_get_max_min_coord(rooms, &sdl->coord);
		rooms = rooms->next;
	}
	sdl_calcul_propreties(sdl);
}

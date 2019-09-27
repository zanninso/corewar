/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_propreties.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 16:12:56 by souarrak          #+#    #+#             */
/*   Updated: 2019/08/06 23:09:30 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl.h"

void	sdl_check_get_max_min_coord(t_room *rooms, t_sdl_coord *coord)
{
	rooms->coord.y > coord->y.max ? coord->y.max = rooms->coord.y : 0;
	rooms->coord.y < coord->y.min ? coord->y.min = rooms->coord.y : 0;
	rooms->coord.x > coord->x.max ? coord->x.max = rooms->coord.x : 0;
	rooms->coord.x < coord->x.min ? coord->x.min = rooms->coord.x : 0;
	rooms->coord.z > coord->z.max ? coord->z.max = rooms->coord.z : 0;
	rooms->coord.z < coord->z.min ? coord->z.min = rooms->coord.z : 0;
}

void	sdl_get_properties(t_room *rooms, t_sdl *sdl)
{
	sdl_init_coord(&sdl->coord);
	while (rooms)
	{
		if ((rooms->is_used && sdl->flag.path) || !sdl->flag.path)
			sdl_check_get_max_min_coord(rooms, &sdl->coord);
		rooms = rooms->next;
	}
	sdl_calcul_propreties(sdl);
}

void	sdl_calcul_propreties(t_sdl *sdl)
{
	sdl->coord.x.altitude = sdl->coord.x.max - sdl->coord.x.min;
	sdl->coord.y.altitude = sdl->coord.y.max - sdl->coord.y.min;
	sdl->coord.z.altitude = sdl->coord.z.max - sdl->coord.z.min;
	if (sdl->coord.x.altitude > sdl->coord.y.altitude)
		sdl->coord.max_altitude = sdl->coord.x.altitude;
	else
		sdl->coord.max_altitude = sdl->coord.y.altitude;
	sdl->coord.x.middle = (sdl->coord.x.max + sdl->coord.x.min) / 2;
	sdl->coord.y.middle = (sdl->coord.y.max + sdl->coord.y.min) / 2;
	sdl->coord.z.middle = (sdl->coord.z.max + sdl->coord.z.min) / 2;
	sdl->zoom = (double)(sdl->coord.max_altitude / sdl->max_zoom_in);
	sdl->zoom > 1 ? sdl->zoom = 1 : 0;
	sdl->zoom < 0 ? sdl->zoom = 0 : 0;
	sdl->zoom_in = sdl->zoom < 1 && sdl->zoom >= 0 ? TRUE : FALSE;
	sdl->zoom_out = sdl->zoom <= 1 && sdl->zoom > 0.0001 ? TRUE : FALSE;
	sdl->radius_rooms = (double)(sdl->zoom * MAX_RADIUS);
	sdl->font.bfs.size = (double)(sdl->zoom * FONT_SIZE_MAX_BFS);
	sdl->font.rooms_name.size = (double)(sdl->zoom * FONT_SIZE_MAX_ROOMS_NAME);
}

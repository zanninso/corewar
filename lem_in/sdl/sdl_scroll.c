/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_scroll.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souarrak <souarrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 19:20:16 by souarrak          #+#    #+#             */
/*   Updated: 2019/08/04 20:59:49 by souarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl.h"

void	sdl_init_scroll(t_room *rooms, t_sdl *sdl)
{
	t_point	point;

	sdl_get_properties(rooms, sdl);
	point.x = MIDDLE_WIDTH - sdl->coord.x.middle;
	point.y = MIDDLE_HEIGHT - sdl->coord.y.middle;
	point.z = 500 - sdl->coord.z.middle;
	sdl_scroll(sdl, point.x, point.y, point.z);
}

void	sdl_scroll(t_sdl *sdl, int scle_x, int scle_y, int scle_z)
{
	t_room	*rooms;

	rooms = sdl->rooms;
	sdl_init_coord(&sdl->coord);
	while (rooms)
	{
		rooms->coord.x = rooms->coord.x + scle_x;
		rooms->coord.y = rooms->coord.y + scle_y;
		rooms->coord.z = rooms->coord.z + scle_z;
		if ((rooms->is_used && sdl->flag.path) || !sdl->flag.path)
			sdl_check_get_max_min_coord(rooms, &sdl->coord);
		if (sdl->flag.pause && rooms->type != 'e')
		{
			rooms->coord_ant.x = rooms->coord_ant.x + scle_x;
			rooms->coord_ant.y = rooms->coord_ant.y + scle_y;
			rooms->coord_ant.z = rooms->coord_ant.z + scle_z;
		}
		rooms = rooms->next;
	}
	sdl_calcul_propreties(sdl);
}

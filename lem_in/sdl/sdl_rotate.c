/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souarrak <souarrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 10:18:22 by souarrak          #+#    #+#             */
/*   Updated: 2019/08/04 21:41:38 by souarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl.h"

void	sdl_rotate_x(t_sdl *sdl, double angle)
{
	double	y0;
	double	z0;
	double	previous_middle_y;
	double	previous_middle_z;
	t_room	*ptr_rooms;

	ptr_rooms = sdl->rooms;
	previous_middle_y = sdl->coord.y.middle;
	previous_middle_z = sdl->coord.z.middle;
	sdl_init_coord(&sdl->coord);
	while (ptr_rooms)
	{
		y0 = ptr_rooms->coord.y;
		z0 = ptr_rooms->coord.z;
		ptr_rooms->coord.y = y0 * cos(angle) + z0 * sin(angle);
		ptr_rooms->coord.z = -y0 * sin(angle) + z0 * cos(angle);
		if ((ptr_rooms->is_used && sdl->flag.path) || !sdl->flag.path)
			sdl_check_get_max_min_coord(ptr_rooms, &sdl->coord);
		ptr_rooms = ptr_rooms->next;
	}
	sdl_calcul_propreties(sdl);
	sdl_scroll(sdl, 0, previous_middle_y - sdl->coord.y.middle,
	previous_middle_z - sdl->coord.z.middle);
}

void	sdl_rotate_y(t_sdl *sdl, double angle)
{
	double	x0;
	double	z0;
	double	previous_middle_x;
	double	previous_middle_z;
	t_room	*ptr_rooms;

	ptr_rooms = sdl->rooms;
	previous_middle_x = sdl->coord.x.middle;
	previous_middle_z = sdl->coord.z.middle;
	sdl_init_coord(&sdl->coord);
	while (ptr_rooms)
	{
		x0 = ptr_rooms->coord.x;
		z0 = ptr_rooms->coord.z;
		ptr_rooms->coord.x = x0 * cos(angle) + z0 * sin(angle);
		ptr_rooms->coord.z = -x0 * sin(angle) + z0 * cos(angle);
		if ((ptr_rooms->is_used && sdl->flag.path) || !sdl->flag.path)
			sdl_check_get_max_min_coord(ptr_rooms, &sdl->coord);
		ptr_rooms = ptr_rooms->next;
	}
	sdl_calcul_propreties(sdl);
	sdl_scroll(sdl, previous_middle_x - sdl->coord.x.middle,
	0, previous_middle_z - sdl->coord.z.middle);
}

void	sdl_rotate_z(t_sdl *sdl, double angle)
{
	double	x0;
	double	y0;
	double	previous_middle_x;
	double	previous_middle_y;
	t_room	*ptr_rooms;

	ptr_rooms = sdl->rooms;
	previous_middle_x = sdl->coord.x.middle;
	previous_middle_y = sdl->coord.y.middle;
	sdl_init_coord(&sdl->coord);
	while (ptr_rooms)
	{
		x0 = ptr_rooms->coord.x;
		y0 = ptr_rooms->coord.y;
		ptr_rooms->coord.x = x0 * cos(angle) - y0 * sin(angle);
		ptr_rooms->coord.y = x0 * sin(angle) + y0 * cos(angle);
		if ((ptr_rooms->is_used && sdl->flag.path) || !sdl->flag.path)
			sdl_check_get_max_min_coord(ptr_rooms, &sdl->coord);
		ptr_rooms = ptr_rooms->next;
	}
	sdl_calcul_propreties(sdl);
	sdl_scroll(sdl, previous_middle_x - sdl->coord.x.middle,
	previous_middle_y - sdl->coord.y.middle, 0);
}

void	sdl_rotate(t_sdl *sdl, double angle_x, double angle_y, double angle_z)
{
	sdl_rotate_x(sdl, angle_x);
	sdl_rotate_y(sdl, angle_y);
	sdl_rotate_z(sdl, angle_z);
}

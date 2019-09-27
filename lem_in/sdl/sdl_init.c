/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 16:04:43 by souarrak          #+#    #+#             */
/*   Updated: 2019/08/06 23:09:30 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl.h"

int			generate_random(int nb)
{
	return ((rand() % nb) * (rand() % 2 ? 1 : -1));
}

void		sdl_init_coord(t_sdl_coord *coord)
{
	coord->x.max = 0;
	coord->x.min = MAX_COORD;
	coord->x.middle = 0;
	coord->x.altitude = 0;
	coord->y.max = 0;
	coord->y.min = MAX_COORD;
	coord->y.middle = 0;
	coord->y.altitude = 0;
	coord->max_altitude = 0;
	coord->z.max = 0;
	coord->z.min = MAX_COORD;
	coord->z.middle = 0;
	coord->z.altitude = 0;
}

static void	sdl_init_structure(t_sdl *sdl)
{
	sdl->is_run = TRUE;
	sdl->zoom_scale = ZOOM_SCALE;
	sdl->scroll_scale = SCROLL_SCALE;
	sdl->mouse.x = WIDTH / 2;
	sdl->mouse.y = HEIGHT / 2;
	sdl->flag.rooms_name = FALSE;
	sdl->flag.help = FALSE;
	sdl->flag.path = FALSE;
	sdl->flag.pause = FALSE;
	sdl->zoom_in = 1;
	sdl->nb_ants_left = sdl->nb_ants;
	sdl->zoom_out = 1;
	sdl->rotate_angle = 0.05;
	sdl->pos_ant = 0;
	sdl->speed_ants = SPEED_ANTS;
}

void		sdl_init_all(t_sdl *sdl)
{
	if (SDL_Init(SDL_INIT_VIDEO) == -1 || TTF_Init() == -1)
		sdl_free_all_allocated_memory(sdl);
	if (!(sdl->window = SDL_CreateWindow("Lem_in", 0, 0, WIDTH, HEIGHT,
					SDL_WINDOW_FULLSCREEN)))
		sdl_free_all_allocated_memory(sdl);
	if (!(sdl->renderer = SDL_CreateRenderer(sdl->window, 0, -1)))
		sdl_free_all_allocated_memory(sdl);
	sdl_init_structure(sdl);
	sdl->max_zoom_in = (double)MIN_ZOOM_IN + (double)sdl->nb_rooms /
		(double)MAX_NB_ROOMS * (double)MAX_ZOOM_IN;
	sdl_init_zoom(sdl);
	if (sdl->flag.coord_z)
		sdl_rotate(sdl, 0.2, -0.2, 0.001);
	else
		sdl_rotate(sdl, 0.0001, 0.0001, 0.0001);
	sdl_init_zoom(sdl);
	sdl->zoom = (double)sdl->coord.max_altitude / (double)sdl->max_zoom_in;
	sdl->radius_rooms = (double)(sdl->zoom * MAX_RADIUS);
	sdl->font.rooms_name.size = sdl->zoom * (double)FONT_SIZE_MAX_ROOMS_NAME;
	sdl->font.rooms_name.color = FONT_COLOR_ROOMS_NAME;
	sdl->font.rooms_name.font = FONT_NAME_ROOMS_NAME;
}

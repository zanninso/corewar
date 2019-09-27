/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_events_keydown.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souarrak <souarrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 23:21:38 by souarrak          #+#    #+#             */
/*   Updated: 2019/08/07 12:00:55 by souarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl.h"

static _Bool	sdl_event_keydown_scroll(t_sdl *sdl)
{
	if (sdl->event.key.keysym.sym == SDLK_RIGHT)
		sdl_scroll(sdl, sdl->scroll_scale, 0, 0);
	else if (sdl->event.key.keysym.sym == SDLK_LEFT)
		sdl_scroll(sdl, -sdl->scroll_scale, 0, 0);
	else if (sdl->event.key.keysym.sym == SDLK_UP)
		sdl_scroll(sdl, 0, sdl->scroll_scale, 0);
	else if (sdl->event.key.keysym.sym == SDLK_DOWN)
		sdl_scroll(sdl, 0, -sdl->scroll_scale, 0);
	else if (sdl->event.key.keysym.sym == SDLK_KP_9)
		sdl->scroll_scale = sdl->scroll_scale + SCROLL_SCALE;
	else if (sdl->event.key.keysym.sym == SDLK_KP_6)
	{
		if (sdl->scroll_scale > SCROLL_SCALE)
			sdl->scroll_scale -= SCROLL_SCALE;
	}
	else
		return (FALSE);
	return (TRUE);
}

static _Bool	sdl_event_keydown_zoom(t_room *rooms, t_sdl *sdl)
{
	if (sdl->event.key.keysym.sym == SDLK_i && sdl->zoom_in)
	{
		sdl->mouse.x = MIDDLE_WIDTH;
		sdl->mouse.y = MIDDLE_HEIGHT;
		sdl_zoom_in(rooms, sdl, sdl->zoom_scale);
	}
	else if (sdl->event.key.keysym.sym == SDLK_o)
	{
		sdl->mouse.x = MIDDLE_WIDTH;
		sdl->mouse.y = MIDDLE_HEIGHT;
		sdl_zoom_out(rooms, sdl, sdl->zoom_scale);
	}
	else if (sdl->event.key.keysym.sym == SDLK_KP_PLUS)
		sdl->zoom_scale = sdl->zoom_scale + ZOOM_SCALE;
	else if (sdl->event.key.keysym.sym == SDLK_KP_MINUS)
		sdl->zoom_scale > ZOOM_SCALE ? sdl->zoom_scale += -ZOOM_SCALE : 0;
	else if (sdl->event.key.keysym.sym == SDLK_SPACE)
	{
		readjust_coord(sdl);
		sdl_init_zoom(sdl);
	}
	else
		return (FALSE);
	return (TRUE);
}

static _Bool	sdl_event_keydown_rotate(t_sdl *sdl)
{
	if (sdl->event.key.keysym.sym == SDLK_a && !sdl->flag.pause)
		sdl_rotate_y(sdl, sdl->rotate_angle);
	else if (sdl->event.key.keysym.sym == SDLK_d && !sdl->flag.pause)
		sdl_rotate_y(sdl, -sdl->rotate_angle);
	else if (sdl->event.key.keysym.sym == SDLK_w && !sdl->flag.pause)
		sdl_rotate_x(sdl, sdl->rotate_angle);
	else if (sdl->event.key.keysym.sym == SDLK_s && !sdl->flag.pause)
		sdl_rotate_x(sdl, -sdl->rotate_angle);
	else if (sdl->event.key.keysym.sym == SDLK_q && !sdl->flag.pause)
		sdl_rotate_z(sdl, -sdl->rotate_angle);
	else if (sdl->event.key.keysym.sym == SDLK_e && !sdl->flag.pause)
		sdl_rotate_z(sdl, sdl->rotate_angle);
	else
		return (FALSE);
	return (TRUE);
}

void			sdl_event_keydown(t_room *rooms, t_sdl *sdl)
{
	if (sdl_event_keydown_scroll(sdl))
		return ;
	else if (sdl_event_keydown_zoom(rooms, sdl))
		return ;
	else if (sdl_event_keydown_rotate(sdl))
		return ;
	else if (sdl->event.key.keysym.sym == SDLK_n)
		sdl->flag.rooms_name = sdl->flag.rooms_name ? FALSE : TRUE;
	else if (sdl->event.key.keysym.sym == SDLK_h)
		sdl->flag.help = sdl->flag.help ? FALSE : TRUE;
	else if (sdl->event.key.keysym.sym == SDLK_c)
	{
		sdl->flag.path = sdl->flag.path ? FALSE : TRUE;
		readjust_coord(sdl);
		sdl_init_zoom(sdl);
	}
	else if (sdl->event.key.keysym.sym == SDLK_p)
		sdl->flag.pause = sdl->flag.pause ? FALSE : TRUE;
	else if (sdl->event.key.keysym.sym == SDLK_KP_8)
		sdl->speed_ants += 0.01;
	else if (sdl->event.key.keysym.sym == SDLK_KP_5)
		sdl->speed_ants > 0.01 ? sdl->speed_ants -= 0.01 : 0;
	else if (sdl->event.key.keysym.sym == SDLK_ESCAPE)
		sdl->is_run = FALSE;
}

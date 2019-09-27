/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_events_mouse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 22:16:59 by souarrak          #+#    #+#             */
/*   Updated: 2019/08/06 19:22:37 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl.h"

void	sdl_event_mouse_button_up(t_room *rooms, t_sdl *sdl)
{
	if (sdl->event.button.clicks == 2
			&& sdl->event.button.button == SDL_BUTTON_LEFT)
		sdl_zoom_in(rooms, sdl, sdl->zoom_scale * 20);
	else if (sdl->event.button.button == SDL_BUTTON_RIGHT)
		sdl_scroll(sdl, MIDDLE_WIDTH - sdl->coord.x.middle,
				MIDDLE_HEIGHT - sdl->coord.y.middle, 0);
	else if (sdl->event.button.button == SDL_BUTTON_MIDDLE)
	{
		sdl_scroll(sdl, MIDDLE_WIDTH - sdl->coord.x.middle,
				MIDDLE_HEIGHT - sdl->coord.y.middle, 0);
		sdl_init_zoom(sdl);
	}
}

void	sdl_event_mouse_motion(t_sdl *sdl)
{
	if (sdl->event.button.button == SDL_BUTTON_LEFT)
		sdl_scroll(sdl, sdl->event.motion.x - sdl->mouse.x,
				sdl->event.motion.y - sdl->mouse.y, 0);
	sdl->mouse.x = sdl->event.motion.x;
	sdl->mouse.y = sdl->event.motion.y;
}

void	sdl_event_mouse_wheel(t_room *rooms, t_sdl *sdl)
{
	if (sdl->event.wheel.y > 0)
		sdl_zoom_in(rooms, sdl, sdl->zoom_scale);
	else if (sdl->event.wheel.y < 0)
		sdl_zoom_out(rooms, sdl, sdl->zoom_scale);
}

void	sdl_event_window(t_room *rooms, t_sdl *sdl)
{
	if (sdl->event.window.event == SDL_WINDOWEVENT_RESIZED)
	{
		sdl_print_graph(rooms, *sdl);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souarrak <souarrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 14:51:38 by souarrak          #+#    #+#             */
/*   Updated: 2019/08/07 11:57:47 by souarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl.h"

void	sdl_print_graph(t_room *rooms, t_sdl sdl)
{
	SDL_Rect rectangle;

	rectangle.x = 0;
	rectangle.y = 0;
	SDL_SetRenderDrawColor(sdl.renderer, COLOR_BACKGROUND, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(sdl.renderer);
	if (sdl.flag.path)
		sdl_print_previous(sdl.end->links, sdl, sdl.renderer);
	else
		sdl_print_links(rooms, &sdl, sdl.renderer);
	sdl_print_rooms(rooms, sdl);
	sdl_print_propreties(sdl, 5, 120, 12);
	if (sdl.flag.help)
		sdl_print_help(sdl, WIDTH - 450, WIDTH - 230, 20);
	else
		stringRGBA(sdl.renderer, WIDTH - 350, 20, "Press 'h' for help", C_HELP);
	SDL_RenderPresent(sdl.renderer);
}

void	sdl_draw_graph(t_sdl *sdl)
{
	sdl_init_all(sdl);
	sdl_print_graph(sdl->rooms, *sdl);
	while (sdl->is_run)
	{
		sdl->event.type = 0;
		SDL_PollEvent(&sdl->event);
		if (!sdl->flag.pause && (sdl->pos_ant || get_ants(sdl, sdl->tab_rooms)))
		{
			sdl_draw_ants(sdl);
			sdl_print_graph(sdl->rooms, *sdl);
		}
		if (sdl->event.type == SDL_KEYDOWN)
			sdl_event_keydown(sdl->rooms, sdl);
		else if (sdl->event.type == SDL_MOUSEBUTTONUP)
			sdl_event_mouse_button_up(sdl->rooms, sdl);
		else if (sdl->event.type == SDL_MOUSEMOTION)
			sdl_event_mouse_motion(sdl);
		else if (sdl->event.type == SDL_MOUSEWHEEL)
			sdl_event_mouse_wheel(sdl->rooms, sdl);
		else if (sdl->event.type == SDL_WINDOWEVENT)
			sdl_event_window(sdl->rooms, sdl);
		else
			continue;
		sdl_print_graph(sdl->rooms, *sdl);
	}
}

void	sdl_get_nb_ants(int *nb_ants, char **line)
{
	int ret;

	while ((ret = get_next_line(0, line)) > 0)
	{
		if (**line != '#')
		{
			*nb_ants = ft_atoi(*line);
			ft_strdel(line);
			return ;
		}
		ft_strdel(line);
	}
	if (ret < 1)
		exit(-1);
}

int		main(void)
{
	t_sdl	sdl;
	char	*line;

	line = NULL;
	sdl.flag.coord_z = FALSE;
	sdl.flag.adjust_rooms = TRUE;
	sdl_get_nb_ants(&sdl.nb_ants, &line);
	sdl_get_rooms(&sdl, &line);
	sdl_generate_table_rooms(&sdl, sdl.nb_rooms);
	sdl_get_links(&sdl, &line);
	sdl_get_paths(&line, &sdl, sdl.tab_rooms);
	sdl.start->previous = NULL;
	sdl.start->is_used = 1;
	sdl.flag.path = FALSE;
	readjust_coord(&sdl);
	sdl_draw_graph(&sdl);
	sdl_free_all_allocated_memory(&sdl);
	return (0);
}

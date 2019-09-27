/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 17:50:49 by souarrak          #+#    #+#             */
/*   Updated: 2019/08/06 20:43:31 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl.h"

void	sdl_free_all_allocated_memory(t_sdl *sdl)
{
	t_link *next_link;
	t_room *next_room;

	while (sdl->rooms)
	{
		next_room = sdl->rooms->next;
		while (sdl->rooms->links)
		{
			next_link = sdl->rooms->links->next;
			ft_memdel((void **)&sdl->rooms->links);
			sdl->rooms->links = next_link;
		}
		ft_strdel(&sdl->rooms->name);
		ft_memdel((void **)&sdl->rooms);
		sdl->rooms = next_room;
	}
	ft_memdel((void **)&sdl->tab_rooms);
	sdl->graph_texture ? SDL_DestroyTexture(sdl->graph_texture) : 0;
	sdl->renderer ? SDL_DestroyRenderer(sdl->renderer) : 0;
	sdl->renderer ? SDL_DestroyWindow(sdl->window) : 0;
	SDL_Quit();
}

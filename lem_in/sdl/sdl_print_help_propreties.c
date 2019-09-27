/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_print_help_propreties.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souarrak <souarrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 15:28:52 by souarrak          #+#    #+#             */
/*   Updated: 2019/08/06 17:58:01 by souarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl.h"

void	sdl_putstr(SDL_Renderer *rend, char *str, t_point p, t_sdl_font_prp prp)
{
	SDL_Rect	text_rect;
	SDL_Surface	*text_surface;
	SDL_Texture	*text_texture;
	TTF_Font	*font;

	font = TTF_OpenFont(prp.font, prp.size);
	text_surface = TTF_RenderText_Solid(font, str, prp.color);
	text_texture = SDL_CreateTextureFromSurface(rend, text_surface);
	text_rect.w = text_surface->w;
	text_rect.h = text_surface->h;
	text_rect.x = p.x - text_rect.w / 2;
	text_rect.y = p.y - text_surface->h / 2;
	TTF_CloseFont(font);
	SDL_FreeSurface(text_surface);
	SDL_QueryTexture(text_texture, NULL, NULL, &text_rect.w, &text_rect.h);
	SDL_RenderCopy(rend, text_texture, NULL, &text_rect);
	SDL_DestroyTexture(text_texture);
}

void	sdl_print_propreties_2(t_sdl sdl, int x0, int x1, int y)
{
	char	*str;

	stringRGBA(sdl.renderer, x0, y += 12, "Ants left", COLOR_PROPRETIES);
	str = ft_itoa(sdl.nb_ants_left);
	stringRGBA(sdl.renderer, x1, y, str, CLR_VAL);
	free(str);
	stringRGBA(sdl.renderer, x0, y += 24, "Status", COLOR_PROPRETIES);
	stringRGBA(sdl.renderer, x1, y, sdl.flag.pause ? "Pause" : "Play", CLR_VAL);
}

void	sdl_print_propreties(t_sdl sdl, int x0, int x1, int y)
{
	char	*str;

	stringRGBA(sdl.renderer, x0, y += 24, "Scroll_scale", COLOR_PROPRETIES);
	str = ft_itoa(sdl.scroll_scale);
	stringRGBA(sdl.renderer, x1, y, str, CLR_VAL);
	free(str);
	stringRGBA(sdl.renderer, x0, y += 12, "Zoom_scale", COLOR_PROPRETIES);
	str = ft_itoa(sdl.zoom_scale * 100);
	stringRGBA(sdl.renderer, x1, y, str, CLR_VAL);
	free(str);
	stringRGBA(sdl.renderer, x0, y += 12, "Speed_ants", COLOR_PROPRETIES);
	str = ft_itoa(sdl.speed_ants * 100);
	stringRGBA(sdl.renderer, x1, y, str, CLR_VAL);
	free(str);
	stringRGBA(sdl.renderer, x0, y += 12, "Zoom", COLOR_PROPRETIES);
	str = ft_itoa(sdl.zoom * 100);
	stringRGBA(sdl.renderer, x1, y, str, CLR_VAL);
	free(str);
	stringRGBA(sdl.renderer, x0, y += 24, "Ants at start", COLOR_PROPRETIES);
	str = ft_itoa(sdl.nb_ants);
	stringRGBA(sdl.renderer, x1, y, str, CLR_VAL);
	free(str);
	sdl_print_propreties_2(sdl, x0, x1, y);
}

void	sdl_print_help_2(t_sdl sdl, int x0, int x1, int y)
{
	stringRGBA(sdl.renderer, x0, y += 24, "Scroll up", COLOR_OPTIONS);
	stringRGBA(sdl.renderer, x1, y, "UP | Mouse motion left", COLOR_KEY_MAP);
	stringRGBA(sdl.renderer, x0, y += 12, "Scroll down", COLOR_OPTIONS);
	stringRGBA(sdl.renderer, x1, y, "DOWN | Mouse motion left", COLOR_KEY_MAP);
	stringRGBA(sdl.renderer, x0, y += 12, "Scroll right", COLOR_OPTIONS);
	stringRGBA(sdl.renderer, x1, y, "RIGHT | Mouse motion left", COLOR_KEY_MAP);
	stringRGBA(sdl.renderer, x0, y += 12, "Scroll left", COLOR_OPTIONS);
	stringRGBA(sdl.renderer, x1, y, "LEFT | Mouse motion left", COLOR_KEY_MAP);
	stringRGBA(sdl.renderer, x0, y += 24, "Default zoom/scroll", COLOR_OPTIONS);
	stringRGBA(sdl.renderer, x1, y, "Space | Mouse wheel but.", COLOR_KEY_MAP);
	stringRGBA(sdl.renderer, x0, y += 12, "Default scroll", COLOR_OPTIONS);
	stringRGBA(sdl.renderer, x1, y, "Mouse right button", COLOR_KEY_MAP);
	stringRGBA(sdl.renderer, x0, y += 12, "Zoom-in", COLOR_OPTIONS);
	stringRGBA(sdl.renderer, x1, y, "'I' | Mouse wheel in", COLOR_KEY_MAP);
	stringRGBA(sdl.renderer, x0, y += 12, "zoom-out", COLOR_OPTIONS);
	stringRGBA(sdl.renderer, x1, y, "'O' | Mouse wheel out", COLOR_KEY_MAP);
	stringRGBA(sdl.renderer, x0, y += 24, "rooms name", COLOR_OPTIONS);
	stringRGBA(sdl.renderer, x1, y, "'n'", COLOR_KEY_MAP);
	stringRGBA(sdl.renderer, x0, y += 12, "Clean graph", COLOR_OPTIONS);
	stringRGBA(sdl.renderer, x1, y, "'c'", COLOR_KEY_MAP);
	stringRGBA(sdl.renderer, x0, y += 12, "Play / Pause", COLOR_OPTIONS);
	stringRGBA(sdl.renderer, x1, y, "'p'", COLOR_KEY_MAP);
	stringRGBA(sdl.renderer, x0, y += 12, "Exit", COLOR_OPTIONS);
	stringRGBA(sdl.renderer, x1, y, "ESC", COLOR_KEY_MAP);
}

void	sdl_print_help(t_sdl sdl, int x0, int x1, int y)
{
	stringRGBA(sdl.renderer, x0, y, "     Option", COLOR_TITLE_OPTION);
	stringRGBA(sdl.renderer, x1, y, "            Key", COLOR_TITLE_KEY);
	stringRGBA(sdl.renderer, x0, y += 24, "zoom speed +", COLOR_OPTIONS);
	stringRGBA(sdl.renderer, x1, y, "'+'", COLOR_KEY_MAP);
	stringRGBA(sdl.renderer, x0, y += 12, "zoom speed -", COLOR_OPTIONS);
	stringRGBA(sdl.renderer, x1, y, "'-'", COLOR_KEY_MAP);
	stringRGBA(sdl.renderer, x0, y += 24, "Speed ants +", COLOR_OPTIONS);
	stringRGBA(sdl.renderer, x1, y, "'8'", COLOR_KEY_MAP);
	stringRGBA(sdl.renderer, x0, y += 12, "Speed ants -", COLOR_OPTIONS);
	stringRGBA(sdl.renderer, x1, y, "'5'", COLOR_KEY_MAP);
	stringRGBA(sdl.renderer, x0, y += 12, "scroll_scale +", COLOR_OPTIONS);
	stringRGBA(sdl.renderer, x1, y, "'9'", COLOR_KEY_MAP);
	stringRGBA(sdl.renderer, x0, y += 12, "zoom_scale -", COLOR_OPTIONS);
	stringRGBA(sdl.renderer, x1, y, "'6'", COLOR_KEY_MAP);
	stringRGBA(sdl.renderer, x0, y += 24, "Rotate X", COLOR_OPTIONS);
	stringRGBA(sdl.renderer, x1, y, "'W' & 'S'", COLOR_KEY_MAP);
	stringRGBA(sdl.renderer, x0, y += 12, "Rotate Y", COLOR_OPTIONS);
	stringRGBA(sdl.renderer, x1, y, "'A' & 'D'", COLOR_KEY_MAP);
	stringRGBA(sdl.renderer, x0, y += 12, "Rotate Z", COLOR_OPTIONS);
	stringRGBA(sdl.renderer, x1, y, "'Q' & 'E'", COLOR_KEY_MAP);
	sdl_print_help_2(sdl, x0, x1, y);
}

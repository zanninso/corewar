/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souarrak <souarrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 14:51:38 by souarrak          #+#    #+#             */
/*   Updated: 2019/08/07 12:18:55 by souarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SDL_H
# define SDL_H

/*
** INCLUDE
*/

# include <stdio.h>
# include "../libft/libft.h"
# include "SDL2/SDL.h"
# include "SDL2/SDL_ttf.h"
# include "SDL2/SDL2_gfxPrimitives.h"

/*
** WINDOW
*/

# define WIDTH 2560
# define HEIGHT 1400

# define SCREEN_WIDTH (WIDTH - 40)
# define SCREEN_HEIGHT (HEIGHT - 40)

# define MIDDLE_WIDTH (WIDTH / 2)
# define MIDDLE_HEIGHT (HEIGHT / 2)

/*
** COORD
*/

# define MAX_COORD INT_MAX
# define MIN_COORD INT_MIN

/*
** ZOOM
*/

# define MAX_ZOOM_IN 1147483
# define MIN_ZOOM_IN 10000
# define ZOOM_SCALE 0.3

/*
** SCROLL_SCALE
*/

# define SCROLL_SCALE 35

/*
** SPEED_ANTS
*/
# define SPEED_ANTS 0.01

/*
** ROOMS_ATT
*/

# define MAX_NB_ROOMS 4000
# define MAX_RADIUS 500

/*
** COLOR_RGBA_CODE
*/

# define RGBA_GREEN 0, 128, 0, 255
# define RGBA_RED 220, 20, 60, 255
# define RGBA_BLUE 0, 76, 153, 255
# define RGBA_WHITE 200, 200, 200, 255
# define RGBA_ORANGE 255, 99, 71, 255

/*
** COLOR_RGB_CODE
*/

# define RGB_DARKBLUE 12, 12, 25
# define RGB_GREY 32, 32, 32
# define RGB_GREEN 0, 128, 0
# define RGB_RED 220, 20, 60
# define RGB_BLUE 0, 76, 153
# define RGB_WHITE 255, 255, 255
# define RGB_ORANGE 255, 99, 71

/*
** BACKGROUND_COLOR
*/

# define COLOR_BACKGROUND 15, 15, 15

/*
** ANT_COLOR
*/

# define COLOR_ANT RGBA_GREEN

/*
** COLOR_ROOMS
*/

# define COLOR_START RGBA_ORANGE
# define COLOR_END RGBA_GREEN
# define COLOR_ROOMS RGBA_BLUE
# define COLOR_ROOMS_PATH RGBA_RED
# define COLOR_ROOMS_LAST_PATH RGBA_GREEN

/*
** COLOR_LINKS
*/

# define COLOR_LINKS RGB_BLUE
# define COLOR_PATHS RGB_RED
# define COLOR_LAST_PATH RGB_GREEN

/*
** COLOR_PROPRETIES & HELP
*/

# define COLOR_TITLE_KEY RGBA_GREEN
# define COLOR_TITLE_OPTION RGBA_GREEN
# define COLOR_KEY_MAP RGBA_RED
# define COLOR_OPTIONS RGBA_WHITE
# define COLOR_PROPRETIES RGBA_GREEN
# define CLR_VAL RGBA_RED
# define C_HELP RGBA_RED

/*
** BFS_FONT
*/

# define FONT_SIZE_MAX_BFS 300
# define FONT_NAME_BFS "calibri.ttf"
# define FONT_COLOR_BFS (SDL_Color){RGB_DARKBLUE}

/*
** ROOMS_NAME_FONT
*/

# define FONT_SIZE_MAX_ROOMS_NAME 300
# define FONT_NAME_ROOMS_NAME "sdl/calibri.ttf"
# define FONT_COLOR_ROOMS_NAME (SDL_Color){RGBA_WHITE}

# define POINT_NULL (t_point){0, 0, 0}

/*
** -------------- GENERAL STRUCTERS --------------
*/

typedef struct	s_point
{
	double	x;
	double	y;
	double	z;
}				t_point;

/*
** ------------- LEM_IN STRUCTURES -------------
*/

typedef struct	s_room
{
	t_point			coord;
	char			*name;
	char			type;
	int				ant;
	_Bool			full;
	_Bool			is_used;
	t_point			coord_ant;
	double			x;
	int				bfs;
	struct s_link	*links;
	struct s_room	*path;
	struct s_room	*previous;
	struct s_room	*next;
}				t_room;

typedef struct	s_link
{
	t_room			*room;
	t_point			coord_ant;
	_Bool			ant;
	_Bool			next_ant;
	struct s_link	*tmp_next;
	struct s_link	*next;
}				t_link;

typedef struct	s_table_rooms
{
	char	*name;
	int		index;
	t_room	*adress;
}				t_tab_rooms;

/*
** ------------- SDL STRUCTURES -------------
*/

typedef struct	s_sdl_font_propreties
{
	int			size;
	char		*font;
	SDL_Color	color;
}				t_sdl_font_prp;

typedef struct	s_sdl_font
{
	t_sdl_font_prp	bfs;
	t_sdl_font_prp	rooms_name;
}				t_sdl_font;

typedef struct	s_sdl_propreties_point
{
	long	max;
	long	min;
	long	middle;
	long	altitude;
}				t_sdl_propreties_point;

typedef struct	s_sdl_coord
{
	t_sdl_propreties_point	x;
	t_sdl_propreties_point	y;
	t_sdl_propreties_point	z;
	long					max_altitude;
}				t_sdl_coord;

typedef struct	s_sdl_flag
{
	_Bool	rooms_name;
	_Bool	coord_z;
	_Bool	adjust_rooms;
	_Bool	help;
	_Bool	path;
	_Bool	pause;
}				t_sdl_flag;

typedef struct	s_sdl
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Texture		*graph_texture;
	SDL_Surface		*graph_surface;
	SDL_Event		event;
	t_sdl_font		font;
	t_room			*rooms;
	t_tab_rooms		*tab_rooms;
	int				nb_rooms;
	int				nb_ants;
	int				nb_ants_left;
	int				nb_paths;
	t_room			*start;
	t_room			*end;
	double			pos_ant;
	double			speed_ants;
	double			zoom;
	_Bool			zoom_in;
	_Bool			zoom_out;
	double			max_zoom_in;
	double			zoom_scale;
	double			radius_rooms;
	int				scroll_scale;
	double			rotate_angle;
	t_point			mouse;
	t_sdl_flag		flag;
	t_sdl_coord		coord;
	_Bool			is_run;
}				t_sdl;

/*
** ----------------------------------SDL_FUNCTIONS------------------------------
*/

/*
** sdl_init
*/
void			sdl_init_all(t_sdl *sdl);

/*
** sdl_coord
*/

void			sdl_init_coord(t_sdl_coord *coord);
void			sdl_check_get_max_min_coord(t_room *rooms, t_sdl_coord *coord);
void			sdl_get_properties(t_room *rooms, t_sdl *sdl);
void			sdl_calcul_propreties(t_sdl *sdl);

/*
** sdl_scroll
*/

void			sdl_init_scroll(t_room *rooms, t_sdl *sdl);
void			sdl_scroll(t_sdl *sdl, int x, int y, int z);

/*
** sdl_zoom
*/

void			sdl_init_zoom(t_sdl *sdl);
void			sdl_zoom_in(t_room *rooms, t_sdl *sdl, double scale);
void			sdl_zoom_out(t_room *rooms, t_sdl *sdl, double scale);

/*
** sdl_roatate
*/

void			sdl_rotate_x(t_sdl *sdl, double angle);
void			sdl_rotate_y(t_sdl *sdl, double angle);
void			sdl_rotate_z(t_sdl *sdl, double angle);
void			sdl_rotate(t_sdl *sdl, double x, double y, double z);

/*
** sdl_ants
*/

_Bool			get_ants(t_sdl *sdl, t_tab_rooms *table_rooms);
void			sdl_draw_ants(t_sdl *sdl);

/*
** sdl_print
*/

void			sdl_print_graph(t_room *rooms, t_sdl sdl);
void			sdl_print_previous(t_link *links, t_sdl sdl, SDL_Renderer *rnd);
void			sdl_print_links(t_room *rooms, t_sdl *sdl, SDL_Renderer *rnd);
void			sdl_print_ants(t_sdl sdl, t_room *rooms, double radius);
void			sdl_print_rooms_circle(t_sdl sdl, t_room *rooms, double radius);
void			sdl_print_rooms(t_room *rooms, t_sdl sdl);
void			sdl_putstr(SDL_Renderer *r, char *s,
				t_point c, t_sdl_font_prp p);
void			sdl_print_propreties(t_sdl sdl, int x0, int x1, int y);
void			sdl_print_help(t_sdl sdl, int x0, int x1, int y);

/*
** events
*/

void			sdl_event_keydown(t_room *rooms, t_sdl *sdl);
void			sdl_event_mouse_button_up(t_room *rooms, t_sdl *sdl);
void			sdl_event_mouse_motion(t_sdl *sdl);
void			sdl_event_mouse_wheel(t_room *rooms, t_sdl *sdl);
void			sdl_event_window(t_room *rooms, t_sdl *sdl);

/*
**-------------------------------LEN_IN_FUNCTIONS-------------------------------
*/

void			sdl_get_rooms(t_sdl *sdl, char **line);
void			sdl_get_links(t_sdl *sdl, char **line);
t_tab_rooms		*sdl_generate_table_rooms(t_sdl *sdl, const int size);
int				sdl_get_room(const char *name, t_tab_rooms *tab_rooms, int nb);
void			sdl_get_paths(char **line, t_sdl *sdl, t_tab_rooms *tab_rooms);
void			readjust_coord(t_sdl *sdl);
int				generate_random(int max);

/*
** --------------------------------FREE_FUNCTIONS-------------------------------
*/

void			sdl_free_all_allocated_memory(t_sdl *sdl);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souarrak <souarrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 16:49:41 by souarrak          #+#    #+#             */
/*   Updated: 2019/09/27 18:19:57 by souarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "../libft/libft.h"
# define MALLOC_ERR "Error : malloc error"
# define MALLOC_ERR_STAT 2
# define NB_ANTS_ERR "Error : ants number not found"
# define NB_ANTS_STAT 3
# define ROOMS_ERR "Error : rooms pattern incorrect"
# define ROOMS_STAT 4
# define ROOMS_NTFND_ERR "Error : start or end rooms not found"
# define ROOMS_NTFND_STAT 5
# define DOUBLE_ROOM_ERR "Error : double rooms"
# define DOUBLE_ROOM_STAT 6
# define LINKS_NTFND_ERR "Error : links not found"
# define LINKS_NTFND_STAT 7
# define GET_LINK_ERR "Error : room's link not found or double link"
# define GET_LINK_STAT 8
# define LINK_ERR "Error : link pattern incorrect"
# define LINK_STAT 9
# define NO_SOLUTION_ERR "Error : no solution found"
# define NO_SOLUTION_STAT 10

typedef struct	s_point
{
	double		x;
	double		y;
	double		z;
}				t_point;

typedef struct	s_rooms
{
	char			*name;
	t_point			coord;
	char			type;
	int				bfs;
	struct s_rooms	*path;
	int				update_bfs;
	_Bool			steps;
	struct s_link	*previous;
	struct s_link	*links;
}				t_rooms;

typedef struct	s_map_line
{
	char				*line;
	char				type;
	struct s_map_line	*next;
}				t_map_line;

typedef struct	s_link
{
	t_rooms			*room;
	int				direct_flow;
	int				*return_flow;
	struct s_link	*previous;
	struct s_link	*next;
}				t_link;

typedef struct	s_t_queue
{
	t_rooms				*room;
	int					level;
	_Bool				correction;
	int					level_correction;
	struct s_t_queue	*next;
}				t_queue;

typedef struct	s_path_room
{
	char				*name;
	int					ant;
	struct s_path_room	*next;
}				t_path_room;

typedef struct	s_path
{
	t_path_room		*rooms;
	struct s_path	*next;
	int				steps;
	int				rate;
}				t_path;

typedef struct	s_lem_in
{
	t_path		*paths_gr1;
	t_path		*paths_gr2;
	t_rooms		*rooms;
	t_rooms		*start;
	t_rooms		*end;
	t_map_line	*map;
	t_queue		*queue;
	char		*start_name;
	char		*end_name;
	size_t		nb_rooms;
	int			nb_ants;
}				t_lem_in;

typedef struct	s_read_map
{
	char		*line;
	t_map_line	*tmp;
	t_map_line	*new;
	char		type;
	char		prev_type;
	_Bool		start_readed;
	_Bool		end_readed;
}				t_read_map;

t_lem_in	g_lem_in;

t_map_line		*get_rooms(t_rooms *rooms, t_map_line *map);
void			get_links(t_map_line *map, t_rooms *rooms);
void			read_map(t_map_line **map);
void			print_rooms(t_rooms *rooms);
void			print_links(int **table_links, t_rooms *rooms, int nb_rooms);
t_rooms			*get_room(t_rooms *rooms, const char *name, int size);
void			sort_last_elem(t_rooms *rooms, size_t i);
void			bfs(t_link *links, int index);
_Bool			cor_flow(t_queue *c_qu, t_queue *lst, t_queue **qu, int lv_qu);
int				count_instructions(t_rooms *start, int nb_ant);
void			add_to_queue(t_queue **queue, t_link *links, int level);
_Bool			increase_flow(t_queue *queue, t_queue *last_node, int level);
_Bool			increase_flow2(t_queue *queue, t_queue *last_node, int level);
void			update_paths(t_rooms *rooms);
void			initialise_update_bfs(t_rooms *rooms, size_t nb_rooms);
_Bool			correction_flow(t_queue *correction_queue, t_queue *last_node,
				t_queue **queue, int level_queue);
t_path			*get_paths_groupe(t_link *links);
void			move_print_ants(t_path *path, int nb_ants);
int				calc_instr(t_path *paths);
void			print_paths(t_path *path, char *start_name);
void			print_map(t_map_line *map);
void			free_and_exit(const char *msg, int status);
void			free_path(t_path **paths);
void			free_queue(t_queue **queues);
void			check_if_start_end_linked(char *flag);

#endif

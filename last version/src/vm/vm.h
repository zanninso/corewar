/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 12:28:38 by souarrak          #+#    #+#             */
/*   Updated: 2019/11/03 22:06:07 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdio.h>
#include <fcntl.h>
#include <time.h>

# define HEADER_SIZE PROG_NAME_LENGTH + COMMENT_LENGTH + 16
# define SIZE_TOTAL HEADER_SIZE + CHAMP_MAX_SIZE
# define MAX_DUMP 64
# define NEGATIVE_CONST 32768
# define PLAYER_CONST 4294967294 

typedef struct s_flag
{
    _Bool   dump;
    _Bool   v;
}   t_flag;

typedef struct s_player
{
    t_header    		header;
	_Bool				full;
	int					live;
	char				prog[CHAMP_MAX_SIZE];
	unsigned char		source_code[SIZE_TOTAL];
	t_process			process;

}               t_player;

typedef struct s_arena
{
	unsigned char	memory[MEM_SIZE];
	int				cycle;
	int	    		cycle_to_die;
	int	    		count_current_cycle;
	int		    	nbr_check;
	int				last_player_alive;
	int		    	nbr_live_current;
	int				nbr_process_alive;
	int				prc_last_id;
    int         	dump_nb_cycles;
	t_process		*process;
}               t_arena;

typedef struct s_vm
{
	WINDOW			*win;
	int				button;
	int				is_running;
	clock_t			time;
	int 			speed;
    t_flag      	flag;
    t_arena     	arena;
	int				nb_players;
    t_player    	player[4];
	t_op op_tab[17];
}				t_vm;


void init_all(t_vm *vm);
void get_input(int argc, char **argv, t_vm *vm);
void print_error(char *msg);
void dump_arena(unsigned char *memory, int size);
void start_war(t_vm *vm);
void print_error(char *msg);
void free_exit(t_vm *vm);
void print_players(t_player player[4], int nb_players);
void print_result(t_vm *vm);
/*
** 
*/
void init_op_tab(t_op *op);
void set_carry(t_process *prc, t_op_component *cmp);
void logical_op(t_process *prc, t_op_component *cmp);
void fork_op(t_process *prc, t_op_component *cmp,t_vm *vm);
void mem_op(t_process *prc, t_op_component *cmp);
int  set_arg(t_vm *vm, t_process *prc, int code);
int get_mem(unsigned char *mem, int addr, int oct);
void set_mem(unsigned char *mem, int addr, int val, int oct);
int exe_op(t_vm *vm, t_process *prc);

void init_win(t_vm *vm);
void refresh_arena(t_vm *vm);
void start_war_vs(t_vm *vm);



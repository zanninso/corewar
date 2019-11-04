/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 11:05:40 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/11/04 03:04:20 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include "op.h"
#include "../../libft/libft.h"
#include "../../ft_printf/src/libftprintf.h"
#define BETWEEN(v, cmp1, cmp2) ((v) >= cmp1 && (v) <= cmp2)
#define ADDR(v) ((MEM_SIZE + (v)) % MEM_SIZE)
#define HEIGHT 100
#define WIDTH 300
#define ESC 27

typedef union u_args {
	char arg4 : 2;
	char arg3 : 2;
	char arg2 : 2;
	char arg1 : 2;
} t_args;

typedef struct s_arg {
	char arg1;
	char arg2;
	char arg3;
} t_arg;

typedef struct s_op {
	char code;
	const char *name;
	char arg_num;
	char arg[3];
	short waiting_cycle;
	_Bool arg_code;
	_Bool carry;
	int size_dir;
	int mod;
	int op_type;
} t_op;

typedef struct s_op_component {
	int code;
	unsigned char arg_code;
	int arg[4];
} t_op_component;

typedef struct s_process {
	int					prc_id;
	int					id_player;
	int					reg[REG_NUMBER + 1];
	_Bool				carry;
	int					pc;
	unsigned char		*memory;
	int					cycle;
	int					cycle_to_die;
	struct s_process	*next;
	t_op_component		cmp;
	_Bool live;
} t_process;

int get_mem(unsigned char *mem, int addr, int oct);
void set_mem(unsigned char *mem, int addr, int val, int oct);

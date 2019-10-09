/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 11:05:40 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/10/09 22:43:00 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include "op.h"

typedef union u_args {
	char arg4 : 2;
	char arg3 : 2;
	char arg2 : 2;
	char arg1 : 2;
} t_args;

typedef union u_op_arg {
	char value;
	t_args args;

} t_op_arg;

typedef struct s_arg {
	char arg1;
	char arg2;
	char arg3;
} t_arg;

typedef struct s_op {
	char code;
	const char *name;
	char arg_num;
	t_arg arg[3];
	short waiting_cycle;
	_Bool arg_code;
	_Bool carry;
	int size_dir;
	int mod;
	int op_type;
} t_op;

typedef struct s_op_component {
	char code;
	t_op_arg arg_code;
	int arg[4];
} t_op_component;

typedef struct s_process {
	int reg[REG_NUMBER];
	_Bool				carry;
	int					pc;
	unsigned char		*memory;
	int					mem_start_pos;
	int					cycle;
	int					cycle_to_die;
	struct s_process	*next;
	t_op_component		cmp;
} t_process;

t_op *op_tab;

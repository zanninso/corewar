/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 11:08:36 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/10/11 00:12:09 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void set_carry(t_process *prc, t_op_component *cmp)
{
	prc->carry = prc->reg[cmp->arg[3]] == 0;
}

void logical_op(t_process *prc, t_op_component *cmp)
{
	if (cmp->code == 2 || cmp->code == 13)
		prc->reg[cmp->arg[1]] = get_mem(prc->memory ,prc->pc + cmp->arg[0], 4);//ok
	if (cmp->code == 4)
		prc->reg[cmp->arg[2]] = cmp->arg[0] + cmp->arg[1];//ok
	if (cmp->code == 5)
		prc->reg[cmp->arg[2]] = cmp->arg[0] - cmp->arg[1]; //ok
	if (cmp->code == 6)
		prc->reg[cmp->arg[2]] = cmp->arg[0] & cmp->arg[1];//ok
	if (cmp->code == 7)
		prc->reg[cmp->arg[2]] = cmp->arg[0] | cmp->arg[1];//ok
	if (cmp->code == 8)
		prc->reg[cmp->arg[2]] = cmp->arg[0] ^ cmp->arg[1];//ok
	if (cmp->code == 9 && prc->carry)
		prc->pc += cmp->arg[0] % IDX_MOD;//ok
	if (cmp->code == 10 || cmp->code == 14)
		prc->reg[cmp->arg[2]] = get_mem(prc->memory , prc->pc + cmp->arg[0] + cmp->arg[1], 4);//ok
	if (cmp->code == 14)
		prc->reg[cmp->arg[2]] = get_mem(prc->memory , prc->pc + (cmp->arg[0] + cmp->arg[1]) % IDX_MOD, 4);//ok
	if(cmp->code == 16)
		ft_putchar(cmp->arg[0]);//ok
	prc->cycle = op_tab[cmp->code].waiting_cycle;
	set_carry(prc,cmp);
}

void fork_op(t_process *prc, t_op_component *cmp)
{
	if (cmp->code == 12)
		add_process(prc, cmp->arg[0] % IDX_MOD);
	if (cmp->code == 15)
		add_process(prc, cmp->arg[0]);
}

void st_op(t_process *prc, t_op_component *cmp)
{
	if (cmp->code == 3)
		set_mem(prc->memory, prc->pc + cmp->arg[1], cmp->arg[0], 4);
	if (cmp->code == 11)
		set_mem(prc->memory, prc->pc + (cmp->arg[1] + cmp->arg[2]) % IDX_MOD,
																cmp->arg[0], 4);
}
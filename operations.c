/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 11:08:36 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/10/09 23:41:34 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void logical_op(t_process *prc, t_op_component *cmp)
{
	if (cmp->code == 2 || cmp->code == 13)
		prc->reg[cmp->arg[2]] = prc->memory[prc->reg[cmp->arg[1]]];
	if (cmp->code == 4)
		prc->reg[cmp->arg[3]] = prc->reg[cmp->arg[1]] + prc->reg[cmp->arg[2]];
	if (cmp->code == 5)
		prc->reg[cmp->arg[3]] = prc->reg[cmp->arg[1]] - prc->reg[cmp->arg[2]];
	if (cmp->code == 6)
		prc->reg[cmp->arg[3]] = prc->reg[cmp->arg[1]] & prc->reg[cmp->arg[2]];
	if (cmp->code == 7)
		prc->reg[cmp->arg[3]] = prc->reg[cmp->arg[1]] | prc->reg[cmp->arg[2]];
	if (cmp->code == 8)
		prc->reg[cmp->arg[3]] = prc->reg[cmp->arg[1]] ^ prc->reg[cmp->arg[2]];
	if (cmp->code == 9)
		prc->pc = cmp->arg[1];
	if (cmp->code == 10 || cmp->code == 14)
		prc->reg[cmp->arg[3]] =
		    prc->memory[prc->reg[cmp->arg[1]] + prc->reg[cmp->arg[2]]];
	prc->cycle = op_tab[cmp->code].waiting_cycle;
	prc->carry = prc->reg[cmp->arg[3]] == 0;
}

void fork_op(t_process *prc, t_op_component *cmp, t_process **last_prc)
{
	int i;
	t_process *new_process;
	if (!(new_process = ft_memalloc(sizeof(t_process))))
		exit(0);
	new_process->carry = prc->carry;
	ft_memcpy(new_process->reg, prc->reg, REG_NUMBER * sizeof(int));
	new_process->memory = prc->memory;
	new_process->cycle_to_die = prc->cycle_to_die;
}

void st_op(t_process *prc, t_op_component *cmp)
{
	prc->memory[cmp->arg[1] + cmp->arg[2]] = prc->reg[cmp->arg[0]];
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 11:08:36 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/09/18 00:35:03 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void logical_op(t_process *prc, t_op_component *cmp)
{
	if (cmp->code == 2 || cmp->code == 13)
		prc->reg[cmp->arg2] =  prc->memory[prc->reg[cmp->arg1]];
	if (cmp->code == 4)
		prc->reg[cmp->arg3] = prc->reg[cmp->arg1] + prc->reg[cmp->arg2];
	if (cmp->code == 5)
		prc->reg[cmp->arg3] = prc->reg[cmp->arg1] - prc->reg[cmp->arg2];
	if (cmp->code == 6)
		prc->reg[cmp->arg3] = prc->reg[cmp->arg1] & prc->reg[cmp->arg2];
	if (cmp->code == 7)
		prc->reg[cmp->arg3] = prc->reg[cmp->arg1] | prc->reg[cmp->arg2];
	if (cmp->code == 8)
		prc->reg[cmp->arg3] = prc->reg[cmp->arg1] ^ prc->reg[cmp->arg2];
	if (cmp->code == 10 || cmp->code == 14)
		prc->reg[cmp->arg3] = prc->memory[prc->reg[cmp->arg1] + prc->reg[cmp->arg2]];
	prc->cycle = op_tab[cmp->code].waiting_cycle;
	prc->carry = prc->reg[cmp->arg3] == 0;
}

void sub(t_process *process, t_op_component *component)
{
	process->reg[component->arg3] = process->reg[component->arg1] - process->reg[component->arg2];
	process->carry = process->reg[component->arg3] == 0;
}

void and (t_process * process, t_op_component *component)
{
	process->reg[component->arg3] =
		process->reg[component->arg1] & process->reg[component->arg2];
	process->carry = process->reg[component->arg3] == 0;
}

void or ()
{
	process->reg[component->arg3] =
		process->reg[component->arg1] & process->reg[component->arg2];
	process->carry = process->reg[component->arg3] == 0;
}

void xor () {

}

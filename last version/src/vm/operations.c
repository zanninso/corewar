/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 11:08:36 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/11/04 09:02:06 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
/*
** op_code|name|arg number|arg type|waiting cycle|arg code|carry|dir size|modulo|op type
*/
void init_op_tab(t_op *op)
{
	op[1] = (t_op){1, "live", 1, {T_DIR}, 10, 0, 0, 4, 0, 0};
	op[2] = (t_op){2, "ld", 2, {T_DIR | T_IND, T_REG}, 5, 1, 1, 4, 1, 3};
	op[3] = (t_op){3, "st", 2, {T_REG, T_IND | T_REG}, 5, 1, 0, 4, 1, 3};
	op[4] = (t_op){4, "add", 3, {T_REG, T_REG, T_REG}, 10, 1, 1, 4, 1, 1};
	op[5] = (t_op){5, "sub", 3, {T_REG, T_REG, T_REG}, 10, 1, 1, 4, 1, 1};
	op[6] = (t_op){6, "and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 1, 1, 4, 1, 1};
	op[7] = (t_op){7, "or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 6, 1, 1, 4, 1, 1};
	op[8] = (t_op){8, "xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 6, 1, 1, 4, 1, 1};
	op[9] = (t_op){9, "zjmp", 1, {T_DIR}, 20, 0, 0, 2, 0, 1};
	op[10] = (t_op){10, "ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 25, 1, 0, 2, 1, 3};
	op[11] = (t_op){11, "sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 25, 1, 0, 2, 1, 3};
	op[12] = (t_op){12, "fork", 1, {T_DIR}, 800, 0, 0, 2, 1, 2};
	op[13] = (t_op){13, "lld", 2, {T_DIR | T_IND, T_REG}, 10, 1, 1, 4, 0, 3};
	op[14] = (t_op){14, "lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 50, 1, 1, 2, 1, 3};
	op[15] = (t_op){15, "lfork", 1, {T_DIR}, 1000, 0, 0, 2, 0, 2};
	op[16] = (t_op){16, "aff", 1, {T_REG}, 2, 1, 0, 4, 0, 1};
}

void set_carry(t_process *prc, t_op_component *cmp)
{
	if (ft_find_int((int[6]){2, 13}, cmp->code, 2, NULL))
		prc->carry = prc->reg[cmp->arg[1]] == 0;
	else 
		prc->carry = prc->reg[cmp->arg[2]] == 0;

}

void logical_op(t_process *prc, t_op_component *cmp)
{
	if (cmp->code == 4)
		prc->reg[cmp->arg[2]] = cmp->arg[0] + cmp->arg[1];
	if (cmp->code == 5)
		prc->reg[cmp->arg[2]] = cmp->arg[0] - cmp->arg[1];
	if (cmp->code == 6)
		prc->reg[cmp->arg[2]] = cmp->arg[0] & cmp->arg[1];
	if (cmp->code == 7)
		prc->reg[cmp->arg[2]] = cmp->arg[0] | cmp->arg[1];
	if (cmp->code == 8)
		prc->reg[cmp->arg[2]] = cmp->arg[0] ^ cmp->arg[1];
	if (cmp->code == 9 && prc->carry)
		prc->pc = (prc->pc - 3) + (cmp->arg[0] % IDX_MOD);
	if (cmp->code == 16)
		ft_putchar(cmp->arg[0]);
}

void fork_op(t_process *prc, t_op_component *cmp, t_vm *vm)
{
	t_process *new;
	int pc;

	if(prc->cmp.code == 12)
		pc = ADDR(prc->pc + cmp->arg[0] % IDX_MOD);
	else 
		pc = ADDR(prc->pc + cmp->arg[0]);
    new = (t_process *)ft_memalloc(sizeof(t_process));
	ft_memcpy(new, prc, sizeof(t_process));
    new->pc = pc;
	new->prc_id = vm->arena.prc_last_id++;
	vm->arena.nbr_process_alive++;
    new->cycle = 0;
    new->next = vm->arena.process;
    vm->arena.process = new;
}

void mem_op(t_process *prc, t_op_component *cmp)
{
	if (cmp->code == 3)
	{
		if((cmp->arg_code >> 4 & 3) == REG_CODE)
			prc->reg[cmp->arg[1]]= cmp->arg[0];
		else
			set_mem(prc->memory, prc->pc + cmp->arg[1], cmp->arg[0], 4);	
	}
	if (cmp->code == 11)
		set_mem(prc->memory, prc->pc + (cmp->arg[1] + cmp->arg[2]) % IDX_MOD, cmp->arg[0], 4);
	if (cmp->code == 2 || cmp->code == 13)
		prc->reg[cmp->arg[1]] = cmp->arg[0];
	if (cmp->code == 10)
		prc->reg[cmp->arg[2]] = get_mem(prc->memory, prc->pc + cmp->arg[0] + cmp->arg[1], 4);
	if (cmp->code == 14)
		prc->reg[cmp->arg[2]] = get_mem(prc->memory, prc->pc + (cmp->arg[0] + cmp->arg[1]) % IDX_MOD, 4);
}
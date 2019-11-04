/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_arg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 17:17:13 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/11/02 23:35:58 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int get_tdir(t_vm *vm, t_process *prc, int pc)
{
	return (get_mem(prc->memory, pc, vm->op_tab[prc->cmp.code].size_dir));
}

int get_tind(t_vm *vm, t_process *prc, int pc)
{
	int addr;

	addr = get_mem(prc->memory, pc, 2);
	if (prc->cmp.code == 3)
		return (addr % IDX_MOD);
	if (prc->cmp.code == 13)
		return (get_mem(prc->memory, prc->pc + addr, 2));
	if (vm->op_tab[prc->cmp.code].mod)
		return (get_mem(prc->memory, prc->pc + addr % IDX_MOD, 4));
	else
		return (get_mem(prc->memory, prc->pc + addr, 4));
}

_Bool get_reg(t_process *prc, int pc, int arg)
{
	if (prc->memory[ADDR(pc)] > 16 || prc->memory[ADDR(pc)] < 1)
		return (0);
	if (ft_find_int((int[3]){2, 3, 13}, prc->cmp.code, 3, NULL) && arg == 1)
		prc->cmp.arg[arg] = prc->memory[ADDR(pc)];
	else if (ft_find_int((int[7]){4, 5, 6, 7, 8, 10, 14},prc->cmp.code, 7, NULL) && arg == 2)
		prc->cmp.arg[arg] = prc->memory[ADDR(pc)];
	else
		prc->cmp.arg[arg] = prc->reg[prc->memory[ADDR(pc)]];
	return (1);
}

int set_arg(t_vm *vm, t_process *prc, int code)
{
	int i;
	int argc;
	int pos;

	i = -1;
	pos = 1 + vm->op_tab[code].arg_code;
	prc->cmp.arg_code = prc->memory[ADDR(prc->pc + 1)];
	while (++i < vm->op_tab[code].arg_num)
	{
		argc = (prc->cmp.arg_code >> (6 - i * 2) & 3);
		argc += argc == 3;
		if (vm->op_tab[code].arg[i] & argc)
		{
			if (argc == T_DIR)
				prc->cmp.arg[i] = get_tdir(vm, prc, ADDR(prc->pc + pos));
			if (argc == T_IND)
				prc->cmp.arg[i] = get_tind(vm, prc, ADDR(prc->pc + pos));
			else if (argc == T_REG && !get_reg(prc, ADDR(prc->pc + pos), i))
				return (0);
		}
		else
			return (0);
		pos += argc != T_DIR ? 1 + (argc == T_IND) : vm->op_tab[code].size_dir;
	}
	return (1);
}
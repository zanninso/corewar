/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_arg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 17:17:13 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/10/10 23:57:34 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int get_tdir(t_process *prc,int pc)
{
	int ret;
	int i;


	i = 0;
	ret = 0;
	while(i < op_tab[prc->cmp.code].size_dir)
		ret = (ret << 8) +  prc->memory[pc + i];
	return (ret);
}


int get_tind(t_process *prc, int pc)
{
	int ret;
	int i;
	int addr;


	i = 0;
	ret = 0;
	addr = (prc->memory[pc] << 8) + prc->memory[pc + 1];
	ret = op_tab[prc->cmp.code].mod ? addr % IDX_MOD : addr;
	return (ret);
}

_Bool get_reg(t_process *prc, int pc,int arg)
{
	int ret;
	int i;
	int addr;
	if(prc->memory[ADDR(pc)] > 16 || prc->memory[ADDR(pc)] < 1)
		return(0);
	if(ft_find_int((int[7]){4, 5, 6, 7, 8, 10, 14}, prc->cmp.code, 7, NULL)
																	&& arg == 3)
		prc->cmp.arg[arg] = prc->memory[ADDR(pc)];
	else if(ft_find_int((int[2]){2, 13}, prc->cmp.code, 2, NULL) && arg == 2)
		prc->cmp.arg[arg] = prc->memory[ADDR(pc)];
	else 
		prc->cmp.arg[arg] = prc->reg[prc->memory[ADDR(pc)]];
	return(1);
}

int  set_arg(t_process *prc, int code)
{
	int i;
    int argc;
	int n = 6;
	int pos;

	i = 0;
	pos = 1;
    prc->cmp.arg_code.value = prc->memory[prc->pc];
	while (i < op_tab[code].arg_num)
	{
        argc = (prc->cmp.arg_code.value >> n);
        argc += argc == 3;
		if(!(op_tab[code].arg[i] & argc))
		{
			if (argc ==  T_DIR)
				prc->cmp.arg[i] = get_tdir(prc, prc->pc + pos);
			if (argc ==  T_IND)
				prc->cmp.arg[i] = get_tind(prc, prc->pc + pos);
			else if (argc == T_REG && !get_reg(prc, prc->pc + pos, i))
				return(0);
			pos += argc != T_DIR ? 1 + (argc ==  T_IND) : op_tab[code].size_dir;
		}
		else
			return(0);
		n -= 2;
		i++;
	}
	prc->pc += pos;
	return(1);
}
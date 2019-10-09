/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_arg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 17:17:13 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/10/09 22:46:13 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

// void get_tdir(t_process *prc, int PC,t_op_component *cmp)
// {
// 	if(arg_code)
// }

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
			else if (argc == T_REG)
				prc->cmp.arg[i] = prc->reg[prc->pc];
			pos += argc != T_DIR ? 1 + (argc ==  T_IND) : op_tab[code].size_dir;
		}
		else
			return(0);
		n -= 2;
		i++;
	}
	return(1);
}
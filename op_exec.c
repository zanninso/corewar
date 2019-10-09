/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 12:28:26 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/10/09 15:07:48 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

_Bool *parse_operation(t_process *prc)
{
	
	int i;
	
	ft_bzero(&prc->cmp,sizeof(t_op_component));
	prc->cmp.code = prc->memory[prc->pc];
	if (prc->cmp.code < 1 || prc->cmp.code > 16)
		return (0);
    prc->pc++;
	if(!set_arg(prc, prc->cmp.code), prc->cmp.code))
        return(0);
    return(1);
}

int exe_op(t_process *prc)
{
    if(parse_operation(prc))
    {
        if(op_tab[prc->cmp.code].op_type == 1)
            return (logical_op(prc, &prc->cmp));
        if(op_tab[prc->cmp.code].op_type == 2)
            return(fork_op(prc, &prc->cmp));
        return(st_op(prc, &prc->cmp));
    }
    return(-1);
}
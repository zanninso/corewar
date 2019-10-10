/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set_mem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 23:32:47 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/10/10 18:32:49 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int get_mem(unsigned char *mem, int addr, int oct)
{
	int ret;
	int i;

	ret = 0;
	i = 0;
	addr = ADDR(addr);
	while (i < oct)
		ret = (ret << 8) + mem[addr + i];
	return (ret);
}

void set_mem(unsigned char *mem, int addr, int val, int oct)
{
	int i;

	i = 0;
	addr = ADDR(addr);
	while (i < oct) 
    {
		mem[addr + i] = val >> (oct - i - 1);
		i++;
	}
}
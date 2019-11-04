/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set_mem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 23:32:47 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/10/31 20:41:42 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int get_mem(unsigned char *mem, int addr, int oct)
{
	long ret;
	int i;

	i = 0;
	ret = 0;
	while (i < oct)
		ret = (ret << 8) + mem[ADDR(addr + i++)];
	if(ret >= 1 << (oct * 8 - 1))
		ret = -(((long)1 << (oct * 8)) - ret); 
	return (ret);
}

void set_mem(unsigned char *mem, int addr, int val, int oct)
{
	int i;

	i = 0;
	if(val < 0)
		val = ((long)1 << (oct  * 8)) + (long)val; 
	while (i < oct) 
    {
		mem[ADDR(addr + i)] = val >> ((oct - i - 1) * 8);
		i++;
	}
}
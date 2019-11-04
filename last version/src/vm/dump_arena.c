/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_arena.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 16:27:32 by souarrak          #+#    #+#             */
/*   Updated: 2019/11/01 01:34:21 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void dump_hex(unsigned char *memory)
{
	const char *tab = "0123456789abcdef";
	int i;

	i = 0;
	while (i < MAX_DUMP)
	{
		ft_printf("%c",tab[memory[i] / 16]);
		ft_printf("%c",tab[memory[i] % 16]);
		i < MAX_DUMP - 1 ? ft_printf(" ") : 0;
		i++;
	}
	ft_printf(" \n");
}

void dump_arena(unsigned char *memory, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		i == 0 ? ft_printf("0x0000 : ") : ft_printf("%#.4x : ", i);
		dump_hex(memory + i);
		i += MAX_DUMP;
	}
}

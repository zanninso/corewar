/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souarrak <souarrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 15:00:30 by souarrak          #+#    #+#             */
/*   Updated: 2019/10/03 17:10:25 by souarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void print_players(t_player player[4], int nb_players)
{
    int i;

    i = 0;
    ft_printf("Introducing contestants...\n");
    while (i < nb_players)
    {
        ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", i + 1, player[i].header.prog_size, player[i].header.prog_name, player[i].header.comment);
        i++;
    }
}

void print_result(t_vm *vm)
{
    dump_arena(vm->arena.memory, MEM_SIZE);
}

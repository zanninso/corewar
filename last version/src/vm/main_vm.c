/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 11:46:55 by souarrak          #+#    #+#             */
/*   Updated: 2019/11/04 02:55:38 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void load_arena(t_vm *vm)
{
    int i;
    t_process *process;
    t_process *ptr;

    i = 0;
    ptr = NULL;
    while (i < vm->nb_players)
    {
        ft_memcpy(vm->arena.memory + (i * MEM_SIZE / vm->nb_players), vm->player[i].prog, vm->player[i].header.prog_size);
        process = (t_process *)ft_memalloc(sizeof(t_process));
        process->pc = i * MEM_SIZE / vm->nb_players;
        process->reg[1] = -(i + 1);
        process->cycle = 0;
        process->memory = vm->arena.memory;
        process->id_player = -(i + 1);
        process->prc_id = vm->arena.prc_last_id++;
        process->next = ptr;
        process->cycle = 0;
        ptr = process;
        vm->arena.nbr_process_alive++;
        i++;
    }
    vm->arena.process = process;
}


int main(int argc, char **argv)
{
    t_vm vm;
    init_all(&vm);
    get_input(argc, argv, &vm);
    // print_players(vm.player, vm.nb_players);
    load_arena(&vm);
    start_war_vs(&vm);
    print_result(&vm);



    getchar();
    endwin();
    return (0);
}

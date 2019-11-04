/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   war.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 14:47:50 by souarrak          #+#    #+#             */
/*   Updated: 2019/11/04 02:45:10 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static t_process *kill_process(t_vm *vm, t_process *process_to_kill)
{
    t_process *ptr;
    ptr = vm->arena.process;
    if (ptr == process_to_kill)
    {
        vm->arena.process = process_to_kill->next;
        ft_memdel((void **)&process_to_kill);
        return (vm->arena.process);
    }
    while (ptr->next != process_to_kill)
        ptr = ptr->next;
    ptr->next = process_to_kill->next;
    ft_memdel((void **)&process_to_kill);
    return (ptr->next);
}

static void execute_op(t_vm *vm)
{
    t_process *process;
    int ret;

    process = vm->arena.process;
    while (process)
    {
        //process->cycle ? process->cycle-- : 0;
        // if (process->cycle <= 0)
        {
            //ft_printf("cycle = %d\n", vm->arena.cycle);
            ret = -exe_op(vm, process);
            // if (ret >= 1 && vm->nb_players)
            //     vm->arena.last_player_alive = ret;
        }
        process = process->next;
    }
}

static void check_arena(t_vm *vm)
{
    t_process *process;

    if (vm->arena.count_current_cycle == vm->arena.cycle_to_die)
    {
        //    ft_printf("---------------->period over--------------------\n");
        //     printf("vm->arena.nbr_check = %d\n", vm->arena.nbr_check);
        //     printf("vm->arena.cycle_to_die = %d\n", vm->arena.cycle_to_die);
        //     printf("vm->arena.nbr_live_current = %d\n", vm->arena.nbr_live_current);
        //     ft_printf("cycle = %d\n", vm->arena.cycle);
        //    ft_printf("---------------------------------------------------\n");
        vm->arena.count_current_cycle = 0;
        vm->arena.nbr_check++;
        process = vm->arena.process;
        while (process)
        {
            if (!process->live)
            {
                process = kill_process(vm, process);
                vm->arena.nbr_process_alive--;
                continue;
            }
            else
                process->live = FALSE;
            process = process ? process->next : NULL;
        }
        if (vm->arena.nbr_live_current >= NBR_LIVE || vm->arena.nbr_check == MAX_CHECKS)
        {
            vm->arena.cycle_to_die -= CYCLE_DELTA;
            vm->arena.nbr_check = 0;
        }
        vm->arena.nbr_live_current = 0;
    }
}

void start_war(t_vm *vm)
{
    while (vm->arena.cycle_to_die > 0 && vm->arena.nbr_process_alive > 0)
    {
        //ft_printf("It is now cycle %d\n", vm->arena.cycle + 1);
        check_arena(vm);
		execute_op(vm);
		
        if (!vm->arena.process || vm->arena.cycle_to_die <= 0)
        {
            ft_printf("cycle = %d\n", vm->arena.cycle);
            printf("No process alive\n");
            // getchar();
            // endwin();
            free_exit(vm);
        }
        if (vm->flag.dump && vm->arena.dump_nb_cycles == vm->arena.cycle)
        {
            dump_arena(vm->arena.memory, MEM_SIZE);
            free_exit(vm);
        }
        // if (vm->arena.cycle == 10000)
        {
            // ft_printf("nb_process_alive = %d\n", vm->arena.nbr_process_alive);
            // ft_printf("vm->arena.nbr_check = %d\n", vm->arena.nbr_check);
            // ft_printf("vm->arena.cycle_to_die = %d\n", vm->arena.cycle_to_die);
            // ft_printf("vm->arena.nbr_live_current = %d\n", vm->arena.nbr_live_current);
            // exit(0);

        }
        //refresh_arena(vm);
        // sleep(0.1);
       
        vm->arena.count_current_cycle++;
        vm->arena.cycle++;
    }
}

clock_t calc_time_delay(t_vm *vm)
{
    return (vm->time + 1000000 / vm->speed);
}

static void handle_buttons(t_vm *vm)
{
    if (vm->button == ' ')
        vm->is_running = !(vm->is_running);
    else if (vm->button == 'e')
        vm->speed++;
    else if (vm->button == 'r')
        vm->speed += 10;
    else if (vm->button == 'e')
        vm->speed--;
    else if (vm->button == 'q')
        vm->speed -= 10;
    vm->is_running = (!vm->arena.nbr_process_alive) ? false : vm->is_running;
    vm->speed = (vm->speed < 1) ? 1 : vm->speed;
    vm->speed = (vm->speed > 1000) ? 1000 : vm->speed;
}

void start_war_vs(t_vm *vm)
{
    int j;

    init_win(vm);
    while ((vm->button = getch()) != ESC)
    {
        j = 0;
        handle_buttons(vm);
        if (vm->button == 's')
        {
            check_arena(vm);
            execute_op(vm);
            vm->arena.count_current_cycle++;
            vm->arena.cycle++;
        }
        else if (vm->button == 'z')
            while (j++ < vm->speed)
            {
                check_arena(vm);
                execute_op(vm);
                vm->arena.count_current_cycle++;
                vm->arena.cycle++;
            }
        else if (vm->is_running && (clock() >= calc_time_delay(vm)))
        {
            vm->time = clock();
            check_arena(vm);
            execute_op(vm);
            vm->arena.count_current_cycle++;
            vm->arena.cycle++;
        }
        refresh_arena(vm);
    }
    getchar();
    endwin();
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_visu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 02:51:56 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/11/03 05:42:49 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void print_arena(t_vm *vm)
{
    int i;
    int j;

    i = 0;
    mvwprintw(vm->win, 0, 0, "");
    while (i < 64)
    {
        j = 0;
        while (j < 64)
        {
            attron(0);
            wprintw(vm->win, " %.2x", vm->arena.memory[64 * i + j]);
            j++;
        }
        i++;
        waddch(vm->win, '\n');
    }
    wrefresh(vm->win);
}

void init_win(t_vm *vm)
{
    initscr();
    keypad(stdscr, true);
    nodelay(stdscr, true);
    curs_set(false);
    cbreak();
    noecho();
    use_default_colors();
    start_color();
    attron(0);
    init_pair(0, COLOR_RED, COLOR_BLACK);
    vm->win = newwin(HEIGHT, WIDTH, 1, 2);
    print_arena(vm);
}

void refresh_arena(t_vm *vm)
{
    t_process *prc;

    prc = vm->arena.process;
    print_arena(vm);
    while (prc)
    {
        mvwprintw(vm->win, prc->pc / 64, prc->pc % 64 * 3, " ");
        wattron(vm->win, A_REVERSE);
        wprintw(vm->win, "%.2x", vm->arena.memory[prc->pc]);
        wattroff(vm->win, A_REVERSE);
        prc = prc->next;
    }
    mvwprintw(vm->win, 5, 200, "speed :\t%d", vm->speed);
    mvwprintw(vm->win, 10, 200, "lives :\t%d", vm->arena.nbr_live_current);
    mvwprintw(vm->win, 11, 200, "nb process :\t%d", vm->arena.nbr_process_alive);
    mvwprintw(vm->win, 15, 200, "cycle :\t%d", vm->arena.cycle);
    mvwprintw(vm->win, 16, 200, "current cycle :\t%d", vm->arena.count_current_cycle);
    mvwprintw(vm->win, 17, 200, "cycle to die :\t%d", vm->arena.cycle_to_die);
    mvwprintw(vm->win, 18, 200, "nbr check :\t%d", vm->arena.nbr_check);
    wrefresh(vm->win);
}
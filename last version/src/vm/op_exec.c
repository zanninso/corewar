/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 12:28:26 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/11/04 03:05:55 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

_Bool parse_operation(t_vm *vm, t_process *prc)
{

    ft_bzero(&prc->cmp.arg, sizeof(int) * 4);
    //prc->cmp.code = prc->memory[prc->pc];
    if (!vm->op_tab[prc->cmp.code].arg_code)
    {
        prc->cmp.arg[0] = get_mem(prc->memory, ADDR(prc->pc + 1), vm->op_tab[prc->cmp.code].size_dir);
        return (TRUE);
    }
    if (!set_arg(vm, prc, prc->cmp.code))
        return (FALSE);
    return (TRUE);
}

int get_op_size(t_vm *vm, t_process *prc)
{
    int ret;
    int i;
    int argc;
    int shift;

    ret = 1 + vm->op_tab[prc->cmp.code].arg_code;
    i = 0;
    if (!vm->op_tab[prc->cmp.code].arg_code)
        ret += vm->op_tab[prc->cmp.code].size_dir;
    else
    {
        shift = 8 - (vm->op_tab[prc->cmp.code].arg_num * 2);
        while (i < vm->op_tab[prc->cmp.code].arg_num)
        {
            argc = prc->cmp.arg_code >> (i * 2 + shift) & 3;
            if (argc == REG_CODE)
                ret += 1;
            else if (argc == DIR_CODE)
                ret += vm->op_tab[prc->cmp.code].size_dir;
            else if (argc == IND_CODE)
                ret += 2;
            i++;
        }
    }
    return (ret);
}

int live(t_vm *vm, t_process *prc)
{
    // if(BETWEEN(prc->cmp.arg[0], -vm->nb_players, -1))
    {
        vm->arena.nbr_live_current++;
        //ft_printf("player %d did live in cycle %d current cycle %d total lives %d\n", -prc->id_player, vm->arena.cycle, vm->arena.count_current_cycle, vm->arena.nbr_live_current);
    }
    prc->live = 1;
    return (prc->cmp.arg[0]);
}

void print_op(t_process *prc, t_vm *vm)
{
    int i;
    int argc;

    i = 0;
    argc = prc->cmp.arg_code;
    ft_printf("P\t%d | %s", prc->prc_id, vm->op_tab[prc->cmp.code].name);
    while (i < vm->op_tab[prc->cmp.code].arg_num)
    {
        argc = prc->cmp.arg_code >> (6 - (i * 2)) & 3;
        if (argc == REG_CODE)
            ft_printf(" r%d", prc->cmp.arg[i]);
        else
            ft_printf(" %d", prc->cmp.arg[i]);
        i++;
    }
    ft_printf("\n");
}

void print_opbin(t_process *prc, t_vm *vm)
{
    int i;
    int op_size;
    char *hex = "0123456789abcdef";

    if (prc->cmp.code == 9 && prc->carry)
        return;
    i = 0;
    op_size = get_op_size(vm, prc);
    while (i < op_size)
    {
        ft_printf("%c%c ", hex[prc->memory[prc->pc + i] / 16], hex[prc->memory[prc->pc + i] % 16]);
        i++;
    }
    ft_printf("\n");
}

void set_op_code(t_process *prc, t_vm *vm)
{
     prc->cmp.code = prc->memory[prc->pc];
    if (BETWEEN(prc->memory[prc->pc], 1, 16))
        prc->cycle = vm->op_tab[prc->cmp.code].waiting_cycle;
}

int exe_op(t_vm *vm, t_process *prc)
{
    int ret;

    ret = 0;
    prc->pc = ADDR(prc->pc);
    if (vm->arena.cycle >= 2750)
        prc->pc += 0;
    if (prc->cycle == 0)
        set_op_code(prc, vm);
    if (prc->cycle > 0)
        prc->cycle--;
    if (prc->cycle == 0)
    {
        if (BETWEEN(prc->cmp.code, 1, 16) && parse_operation(vm, prc))
        {
            if (vm->op_tab[prc->cmp.code].op_type == 1)
                logical_op(prc, &prc->cmp);
            else if (vm->op_tab[prc->cmp.code].op_type == 2)
                fork_op(prc, &prc->cmp, vm);
            else if (vm->op_tab[prc->cmp.code].op_type == 3)
                mem_op(prc, &prc->cmp);
            else
                ret = live(vm, prc);
            // print_opbin(prc, vm);
            vm->op_tab[prc->cmp.code].carry ? set_carry(prc, &prc->cmp) : 0;
            prc->pc = ADDR(prc->pc + get_op_size(vm, prc));
        }
        else if(BETWEEN(prc->cmp.code, 1, 16))
        {
            // print_opbin(prc, vm);
             prc->pc = ADDR(prc->pc + get_op_size(vm, prc));
        }
        else 
            prc->pc = ADDR(prc->pc + 1);
    }
    return (ret);
}

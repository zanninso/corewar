/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souarrak <souarrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 14:53:23 by souarrak          #+#    #+#             */
/*   Updated: 2019/10/03 15:13:47 by souarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void print_error(char *msg)
{
    ft_putendl(msg);
    exit(-1);
}

void free_exit(t_vm *vm)
{
    t_process *ptr;

    ptr = vm->arena.process ? vm->arena.process->next : NULL;
    while (vm->arena.process)
    {
        ft_memdel((void **)&vm->arena.process);
        vm->arena.process = ptr;
        vm->arena.process ? ptr = vm->arena.process->next : 0;
    }
    exit (0);
}
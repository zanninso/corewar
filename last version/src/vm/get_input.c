/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 15:45:11 by souarrak          #+#    #+#             */
/*   Updated: 2019/11/02 00:56:15 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

unsigned int get_int(unsigned char *source_code)
{
	unsigned int nb;
	int i;

	i = 3;
	nb = 0;
	while (i >= 0)
	{
		nb = nb + (source_code[i] << (3 - i) * 8);
		i--;
	}
	return (nb);
}

void check_get_player(t_vm *vm, char *argv, int id)
{
    int fd;
	int ret;

    if ((fd = open(argv, O_RDONLY)) <= 0)
        print_error("Error : Can't read source file");
    if (vm->player[id].full)
        print_error("Error : ID player repeated");
	if ((ret = read(fd, vm->player[id].source_code, SIZE_TOTAL)) <= 0)
		print_error("Error : Can't read source file");
	vm->player[id].header.magic = get_int(vm->player[id].source_code);
	if (vm->player[id].header.magic != COREWAR_EXEC_MAGIC)
		print_error("Error : Header magic not compatible");
	vm->player[id].header.prog_size = get_int(&vm->player[id].source_code[PROG_NAME_LENGTH + 8]);
	if (vm->player[id].header.prog_size > CHAMP_MAX_SIZE)
		print_error("Error : source file > Size_Max");
	ft_memcpy(vm->player[id].prog, vm->player[id].source_code + HEADER_SIZE, vm->player[id].header.prog_size);
	ft_memcpy(vm->player[id].header.prog_name, vm->player[id].source_code + 4, PROG_NAME_LENGTH);
	ft_memcpy(vm->player[id].header.comment, vm->player[id].source_code + PROG_NAME_LENGTH + 12, COMMENT_LENGTH);
	vm->nb_players++;
	vm->player[id].full = TRUE;
}

void get_input(int argc, char **argv, t_vm *vm)
{
    int i;
	int	id;

    i = 1;
	id = 0;
    while (i < argc)
    {
        if (ft_strequ(argv[i], "-dump") || ft_strequ(argv[i], "-d"))
        {
            if (!vm->flag.dump)
            {
                vm->flag.dump = 1;
                i + 1 < argc ? vm->arena.dump_nb_cycles = ft_atoi(argv[i + 1]) : print_error("Input_error");
            }
			i++;
        }
		else
		{
        	check_get_player(vm, argv[i], id);
			id++;
		}
        i++;
    }
}

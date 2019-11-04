# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/28 15:53:12 by souarrak          #+#    #+#              #
#    Updated: 2019/11/03 19:50:22 by aait-ihi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VM = vm

LIB_FT = libft/libft.a

LIB_PRINTF = ft_printf/libftprintf.a

VM_SRC =  src/vm/main_vm.c\
			src/vm/get_input.c\
			src/vm/init.c\
			src/vm/dump_arena.c\
			src/vm/war.c\
			src/vm/print.c\
			src/vm/free_exit.c\
			src/vm/get_set_mem.c\
			src/vm/op_arg.c\
			src/vm/op_exec.c\
			src/vm/operations.c\
			src/vm/basic_visu.c

VM_OBJ = $(VM_SRC:%c=%o)

INCLUDE = -I ./include

CC = gcc

#CFLAGS = -Wall -Werror -Wextra -g
CFLAGS =  -g
all : $(VM)

$(LIB_FT) :
	make re -C libft

$(LIB_PRINTF) :
	make re -C ft_printf

$(VM) : $(VM_OBJ)
	$(CC) -g -lncurses $(CFLAGS) $(INCLUDE) $(LIB_FT) $(LIB_PRINTF) $(VM_OBJ) -o $(VM)

clean :
	# make clean -C libft
	# make clean -C ft_printf
	/bin/rm -rf $(VM_OBJ)

fclean : clean
	# make fclean -C libft
	# make fclean -C ft_printf
	/bin/rm -rf $(VM)

re : fclean all

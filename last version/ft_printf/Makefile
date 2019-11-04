# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: souarrak <souarrak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/25 21:12:28 by souarrak          #+#    #+#              #
#    Updated: 2019/10/03 12:58:19 by souarrak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
SRC = ./src/ft_printf.c\
	./src/dispatcher.c\
	./src/get_options.c\
	./src/set_options.c\
	./src/set_color.c\
	./src/set_flags.c\
	./src/va_arg.c\
	./src/get_flags.c\

OBJ = ft_printf.o\
	dispatcher.o\
	get_options.o\
	set_options.o\
	set_color.o\
	set_flags.o\
	va_arg.o\
	get_flags.o\

LIBFTOBJ = ../libft/ft_atoi.o\
	../libft/ft_bzero.o\
	../libft/ft_count_words.o\
	../libft/ft_indexof.o\
	../libft/ft_isalnum.o\
	../libft/ft_isalpha.o\
	../libft/ft_isascii.o\
	../libft/ft_isdigit.o\
	../libft/ft_isln.o\
	../libft/ft_isprint.o\
	../libft/ft_isnbr.o\
	../libft/ft_isinstr.o\
	../libft/ft_iswhitespace.o\
	../libft/ft_itoa.o\
	../libft/ft_lstadd.o\
	../libft/ft_lstdel.o\
	../libft/ft_lstdelone.o\
	../libft/ft_lstiter.o\
	../libft/ft_lstmap.o\
	../libft/ft_lstnew.o\
	../libft/ft_max.o\
	../libft/ft_memalloc.o\
	../libft/ft_memccpy.o\
	../libft/ft_memchr.o\
	../libft/ft_memcmp.o\
	../libft/ft_memcpy.o\
	../libft/ft_memdel.o\
	../libft/ft_memmove.o\
	../libft/ft_memset.o\
	../libft/ft_nblen.o\
	../libft/ft_putchar.o\
	../libft/ft_putchar_fd.o\
	../libft/ft_putendl.o\
	../libft/ft_putendl_fd.o\
	../libft/ft_putnbr.o\
	../libft/ft_putnbr_fd.o\
	../libft/ft_putstr.o\
	../libft/ft_putstr_fd.o\
	../libft/ft_realloc.o\
	../libft/ft_strcat.o\
	../libft/ft_strchr.o\
	../libft/ft_strclr.o\
	../libft/ft_strcmp.o\
	../libft/ft_strcpy.o\
	../libft/ft_strdel.o\
	../libft/ft_strdup.o\
	../libft/ft_strequ.o\
	../libft/ft_strinv.o\
	../libft/ft_striter.o\
	../libft/ft_striteri.o\
	../libft/ft_strjoin.o\
	../libft/ft_strlcat.o\
	../libft/ft_strlen.o\
	../libft/ft_strmap.o\
	../libft/ft_strmapi.o\
	../libft/ft_strncat.o\
	../libft/ft_strncmp.o\
	../libft/ft_strncpy.o\
	../libft/ft_strndup.o\
	../libft/ft_strnequ.o\
	../libft/ft_strnew.o\
	../libft/ft_strnstr.o\
	../libft/ft_strrchr.o\
	../libft/ft_strsplit.o\
	../libft/ft_strstr.o\
	../libft/ft_strsub.o\
	../libft/ft_strtrim.o\
	../libft/ft_tolower.o\
	../libft/ft_toupper.o\
	../libft/ft_isnbr.o\
	../libft/ft_isinstr.o\
	../libft/get_next_line.o\
	../libft/ft_uitoa.o\
	../libft/ft_itoa_base.o\
	../libft/ft_uitoa_base.o\
	../libft/ft_atol.o\
	../libft/ft_reverse_bits.o\
	../libft/special_case.o\
	../libft/ft_pow.o\
	../libft/ft_strtoupper.o\
	../libft/ft_ldtoa.o\
	../libft/ft_strtoupper.o\
	../libft/aritmitic_op.o\
	../libft/conditional_op.o\
	../libft/ft_bipow.o\

all : $(NAME)

$(NAME):
	@make -C ../libft/ fclean && make -C ../libft/
	@gcc -c -Wall -Wextra -Werror $(SRC)
	@ar rc $(NAME) $(OBJ) $(LIBFTOBJ)

clean :
	@/bin/rm -f *.o
	@make -C ../libft/ clean

fclean : clean
	@/bin/rm -f $(NAME)
	@make -C ../libft/ fclean

re : fclean all

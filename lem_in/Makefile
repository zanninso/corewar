# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: souarrak <souarrak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/06 18:42:03 by aait-ihi          #+#    #+#              #
#    Updated: 2019/09/27 17:41:16 by souarrak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VISU = visualiser

LEM_IN = lem-in

SDL_PATH = ~/brew/Cellar/sdl2/2.0.9_1

SDL_GFX_PATH = ~/brew/Cellar/sdl2_gfx/1.0.4

SDL_TTF_PATH = ~/brew/Cellar/sdl2_ttf/2.0.15

LIB_FT = libft/libft.a

VISU_LIB =	-L $(SDL_PATH)/lib -l SDL2\
			-L $(SDL_TTF_PATH)/lib -l SDL2_ttf\
			-L $(SDL_GFX_PATH)/lib -l SDL2_gfx\
			$(LIB_FT)

VISU_INCLUDE =	-I $(SDL_PATH)/include\
				-I $(SDL_PATH)/include/SDL2\
				-I $(SDL_GFX_PATH)/include\
				-I $(SDL_TTF_PATH)/include

VISU_SRC =  sdl/main.c sdl/sdl_adjust_rooms.c sdl/sdl_ants.c sdl/sdl_events_keydown.c\
            sdl/sdl_events_mouse.c sdl/sdl_free.c sdl/sdl_get_links_previous.c sdl/sdl_get_rooms.c\
            sdl/sdl_init.c sdl/sdl_print.c sdl/sdl_print_help_propreties.c sdl/sdl_propreties.c\
            sdl/sdl_rooms_table.c sdl/sdl_rotate.c sdl/sdl_scroll.c sdl/sdl_zoom.c

VISU_OBJ = $(VISU_SRC:%c=%o)

LEM_IN_SRC =	src/calcul_instructions.c src/free_memory.c src/get_rooms.c src/main.c\
            	src/print.c src/read_map.c src/rooms_table.c src/update_flow.c

LEM_IN_OBJ = $(LEM_IN_SRC:%c=%o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror $(VISU_INCLUDE)

all : $(VISU) $(LEM_IN)

$(LIB_FT) :
	make re -C libft

$(VISU) : $(VISU_OBJ) $(LIB_FT) sdl/sdl.h
	$(CC) -o $(VISU) $(CFLAGS) $(VISU_OBJ) $(VISU_LIB)

$(LEM_IN) : $(LEM_IN_OBJ) $(LIB_FT) src/lem_in.h
	$(CC) -g -o $(LEM_IN) $(CFLAGS) $(LEM_IN_OBJ) $(LIB_FT)

clean :
	make clean -C libft
	/bin/rm -rf $(VISU_OBJ) $(LEM_IN_OBJ)

fclean : clean
	make fclean -C libft
	/bin/rm -rf $(VISU) $(LEM_IN)

re : fclean all
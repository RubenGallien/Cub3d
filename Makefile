# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/02 14:25:51 by lvicino           #+#    #+#              #
#    Updated: 2024/10/04 10:57:13 by rgallien         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D

LIBFT		=	libft/libft.a

MLX			=	mlx_linux

BUILD_DIR	=	build


SRC_DIR		=	src

MAIN		=	main.c

MAIN		:=	$(MAIN:%=$(SRC_DIR)/%)
MAIN_OBJ	=	$(MAIN:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
MAIN_DEP	=	$(MAIN_OBJ:$(BUILD_DIR)/%.o=$(BUILD_DIR)/%.d)



PARSING_DIR	=	src/parsing

PARSING		=	parsing.c

PARSING		:=	$(PARSING:%=$(PARSING_DIR)/%)
PARSING_OBJ	=	$(PARSING:$(PARSING_DIR)/%.c=$(BUILD_DIR)/%.o)
PARSING_DEP	=	$(PARSING_OBJ:$(BUILD_DIR)/%.o=$(BUILD_DIR)/%.d)



EXEC_DIR	=	src/exec

EXEC		=	events.c \
				init.c \
				raycasting.c \
				utils.c \

EXEC		:=	$(EXEC:%=$(EXEC_DIR)/%)
EXEC_OBJ	=	$(EXEC:$(EXEC_DIR)/%.c=$(BUILD_DIR)/%.o)
EXEC_DEP	=	$(EXEC_OBJ:$(BUILD_DIR)/%.o=$(BUILD_DIR)/%.d)



CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -MMD -MP -g3
INCLUDE		=	-I include \
				-I libft/include \
				-I libft/ft_printf/include \
				-I libft/get_next_line/include \
				-I/usr/include -Imlx_linux -O3

MAKEFLAGS	+=	--no-print-directory
DIR_DUP		=	mkdir -p $(@D)


all		:	foo $(NAME)

$(NAME)		:	$(MAIN_OBJ) $(PARSING_OBJ) $(EXEC_OBJ)
	@if [ ! -e "$(LIBFT)" ]; then \
		make -C libft; \
	fi
	$(CC) $(MAIN_OBJ) $(PARSING_OBJ) $(EXEC_OBJ) $(LIBFT) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -O3 -ffast-math -lm -lz -o $(NAME)


$(BUILD_DIR)/%.o	:	$(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<


$(BUILD_DIR)/%.o		:	$(PARSING_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<


$(BUILD_DIR)/%.o		:	$(EXEC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<


-include $(MAIN_DEP) $(PARSING_DEP) $(EXEC_DEP)

foo:
	@if [ -d "$(MLX)" ] && [ -d "$(BUILD_DIR)" ]; then \
		echo "make: Nothing to be done for 'all'."; \
	fi
	@if [ ! -d "$(MLX)" ]; then \
		git clone https://github.com/42Paris/minilibx-linux.git ; \
		mv minilibx-linux $(MLX) ; \
		make -C $(MLX) ; \
	fi

clean	:
	if [ -d "$(BUILD_DIR)" ]; then \
		rm -f $(MAIN_OBJ); \
		rm -f $(MAIN_DEP); \
		rm -rf $(BUILD_DIR); \
		make clean -C libft; \
	fi

fclean	:	clean
	if [ -e "$(NAME)" ]; then \
		rm -f $(NAME); \
	fi
	if [ -e "$(LIBFT)" ]; then \
		make fclean -C libft; \
	fi
	if [ -e "$(MLX)" ]; then \
		rm -rf $(MLX); \
	fi

re		:	fclean all

.PHONY	:	clean fclean re
.SILENT	:	clean fclean
